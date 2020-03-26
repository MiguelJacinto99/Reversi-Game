#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "estado.h"

int main() {
    int a = 0;
    int l = 0;
    int c = 0;
    int i = 0;
    int z = 0;
    int verifica = 0;
    int contaEstado = 0;
    int contaEstadoBot = 0;
    int contaComandos = 0;
    int contaExit = 0;
    int nivel = 0;
    int contaValidas = 0;
    ESTADO e = {0};
    char comando [200];
    char text [200];
    for (i = 0; i < 200; i++) {
        comando [i] = ' ';
        text [i] = ' ';
    }
    comando [i] = '\0';
    text [i] = '\0';
    char vencedor = 'W';
    char p = 'P';
    LL llig = NULL;
    FILE *f;
    printf("\nBem-Vindo ao Reversi!\n");
    printf("\nReversi > ");
    while (contaExit == 0) {
        fgets(comando,BUFFERSIZE,stdin);
        switch (toupper(comando[0])) {
            case 'N': {
                verifica = verificaSpaces(comando,3);
                if (verifica == 0 && isspace(comando[1])) {
                    p = toupper(comando[2]);
                    if (p != 'X' && p != 'O') {
                        printf("\nPeça Inválida.\n");
                        printf("\nReversi > ");
                    }
                    else {
                        if (p == 'X') {
                            e.peca = VALOR_X;
                        }
                        if (p == 'O') {
                            e.peca = VALOR_O;
                        }
                        e.modo = 'M';
                        e = mapaInicial(e);
                        freeL(llig);
                        llig = NULL;
                        llig = pushEstado(llig,e);
                        contaEstado = contaEstado + 1;
                        contaEstadoBot = 0;
                        printa(e);
                        printf("\nReversi > ");
                    }
                }
                else {
                    printf("\nComando Inválido. Insira de Novo.\n");
                    printf("\nReversi > ");
                }
                for (i = 0; i < 200; i++) {
                    comando[i] = ' ';
                }
                comando[i] = '\0';
                break;
            }
            case 'L': {
                i = 2;
                z = 0;
                while (comando[i] != ' ' && comando[i]) {
                    text[z] = comando[i];
                    z = z + 1;
                    i = i + 1;
                }
                text[z] = '\0';
                verifica = verificaSpaces(comando,i);
                if (verifica == 0 && isspace(comando[1])) {
                    if ((f = fopen (text, "r")) == NULL) {
                        printf("\nO Ficheiro Inserido Não Existe.\n");
                        printf("\nReversi > ");
                    }
                    else {
                        if (extraiModo(text) == 0) {
                            freeL(llig);
                            llig = NULL;
                            e = loads(e,text);
                            llig = pushEstado(llig,e);
                            contaEstado = contaEstado + 1;
                            printf("\nO Estado Gravado Anteriormente Foi Carregado com Sucesso!\n");
                            printa(e);
                            printf("\nReversi > ");
                        }
                        else {
                            freeL(llig);
                            llig = NULL;
                            e = loadsBOT(e,text);
                            llig = pushEstado(llig,e);
                            contaEstadoBot = contaEstadoBot + 1;
                            nivel = extraiNivel(text);
                            printf("\nO Estado Gravado Anteriormente Foi Carregado com Sucesso!\n");
                            printaBot(e,nivel);
                            printf("\nReversi > ");
                        }
                    }
                }
                else {
                    printf("\nComando Inválido. Insira de Novo.\n");
                    printf("\nReversi > ");
                }
                for (i = 0; i < 200; i++) {
                    comando[i] = ' ';
                    text[i] = ' ';
                }
                comando[i] = '\0';
                text[i] = '\0';
                break;
            }
            case 'E': {
                i = 2;
                z = 0;
                while (comando[i] != ' ' && comando[i]) {
                    text[z] = comando[i];
                    z = z + 1;
                    i = i + 1;
                }
                text[z] = '\0';
                verifica = verificaSpaces(comando,i);
                if (verifica == 0 && isspace(comando[1])) {
                    if (contaEstado != 0 && contaEstadoBot == 0) {
                        saves(e,text);
                        printf("\nO Estado Atual Foi Gravado Com Sucesso!\n");
                        printa(e);
                        printf("\nReversi > ");
                    }
                    else if (contaEstado == 0 && contaEstadoBot != 0) {
                        savesBOT(e,text,nivel);
                        printf("\nO Estado Atual Foi Gravado Com Sucesso!\n");
                        printaBot(e,nivel);
                        printf("\nReversi > ");
                    }
                    else {
                        printf("\nÉ Necessário Iniciar um Jogo Antes de o Gravar.\n");
                        printf("\nReversi > ");
                    }
                }
                else {
                    printf("\nComando Inválido. Insira de Novo.\n");
                    printf("\nReversi > ");
                }
                for (i = 0; i < 200; i++) {
                    comando[i] = ' ';
                    text[i] = ' ';
                }
                comando[i] = '\0';
                text[i] = '\0';
                break;
            }
            case 'J': {
                verifica = verificaSpaces(comando,5);
                if (verifica == 0 && isspace(comando[1]) && isspace(comando[3])) {
                    if (contaEstado != 0 && contaEstadoBot == 0) {
                        l = (int)(comando[2]);
                        c = (int)(comando[4]);
                        l = l - 48;
                        c = c - 48;
                        if (l >= 0 && l < 8 && c >= 0 && c < 8) {
                            e = verificaLinha(e);
                            e = verificaColuna(e);
                            e = verificaDiagonal(e);
                            escondePontos(e);
                            printf("Número de Jogadas Válidas: %d\n", contaJogadasValidas(e));
                            a = 1;
                            a = jogadaValida (e, l, c);
                            if (a == 0) {
                                printf("\nA Jogada Será Realizada na Posição %d %d!\n",l,c);
                                e = converte (e,l,c);
                                e = limpaPontos(e);
                                printa(e);
                                e = trocaJogador(e);
                                llig = pushEstado(llig,e);
                                e = verificaLinha(e);
                                e = verificaColuna(e);
                                e = verificaDiagonal(e);
                                contaValidas = contaJogadasValidas(e);
                                if (fimDeJogo(e) == 1) {
                                    printf("\nNenhum dos Jogadores Têm Mais Jogadas Disponíveis. O Jogo Terminou!\n");
                                    vencedor = contaScore(e);
                                    if (vencedor == '?') {
                                        printf("\nUau! O Jogo Terminou Empatado!\n");
                                    }
                                    else {
                                        printf("O Vencedor do Jogo Foi o Jogador %c!\n",vencedor);
                                        printa(e);
                                    }
                                    freeL(llig);
                                    llig = NULL;
                                    contaEstado = 0;
                                    contaEstadoBot = 0;
                                    printf("\nReversi > ");
                                }
                                else if (contaValidas == 0) {
                                    e = situacaoDeSkip(e);
                                    escondePontos(e);
                                    printf("\nReversi > ");
                                }
                                else {
                                    escondePontos(e);
                                    printf("\nReversi > ");
                                }
                            }
                            else {
                                printf("\nA Jogada Não é Válida. Clique S ou H.\n");
                                printf("\nReversi > ");
                            }
                        }
                        else {
                            printf("\nOs Valores Inseridos São Inválidos.\n");
                            printf("\nReversi > ");
                        }
                    }
                    else if (contaEstado == 0 && contaEstadoBot != 0) {
                        l = (int)(comando[2]);
                        c = (int)(comando[4]);
                        l = l - 48;
                        c = c - 48;
                        if (l >= 0 && l < 8 && c >= 0 && c < 8) {
                            e = verificaLinha(e);
                            e = verificaColuna(e);
                            e = verificaDiagonal(e);
                            escondePontosBOT(e,nivel);
                            printf("Número de Jogadas Válidas: %d\n", contaJogadasValidas(e));
                            a = 1;
                            a = jogadaValida (e, l, c);
                            if (a == 0) {
                                printf("\nA Jogada Será Realizada na Posição %d %d!\n",l,c);
                                e = converte (e,l,c);
                                e = limpaPontos(e);
                                printaBot(e,nivel);
                                e = trocaJogador(e);
                                llig = pushEstado(llig,e);
                                if (nivel == 1) {
                                    e = jogadaBotEasy(e,nivel);
                                    llig = pushEstado(llig,e);
                                    printaBot(e,nivel);
                                    e = verificaLinha(e);
                                    e = verificaColuna(e);
                                    e = verificaDiagonal(e);
                                    contaValidas = contaJogadasValidas(e);
                                    if (fimDeJogo(e) == 1) {
                                        printf("\nNenhum dos Jogadores Têm Mais Jogadas Disponíveis. O Jogo Terminou!\n");
                                        vencedor = contaScore(e);
                                        if (vencedor == '?') {
                                            printf("\nUau! O Jogo Terminou Empatado!\n");
                                        }
                                        else {
                                            printf("O Vencedor do Jogo Foi o Jogador %c!\n",vencedor);
                                            printa(e);
                                        }
                                        freeL(llig);
                                        llig = NULL;
                                        contaEstado = 0;
                                        contaEstadoBot = 0;
                                        printf("\nReversi > ");
                                    }
                                    else if (contaValidas == 0) {
                                        e = situacaoDeSkip(e);
                                        escondePontosBOT(e,nivel);
                                        e = jogadaBotEasy(e,nivel);
                                        llig = pushEstado(llig,e);
                                        printaBot(e,nivel);
                                        printf("\nReversi > ");
                                    }
                                    else {
                                        e = limpaPontos(e);
                                        printf("\nReversi > ");
                                    }
                                }
                                if (nivel == 2) {
                                    e = jogadaBotMedium(e,nivel);
                                    llig = pushEstado(llig,e);
                                    printaBot(e,nivel);
                                    e = verificaLinha(e);
                                    e = verificaColuna(e);
                                    e = verificaDiagonal(e);
                                    contaValidas = contaJogadasValidas(e);
                                    if (fimDeJogo(e) == 1) {
                                        printf("\nNenhum dos Jogadores Têm Mais Jogadas Disponíveis. O Jogo Terminou!\n");
                                        vencedor = contaScore(e);
                                        if (vencedor == '?') {
                                            printf("\nUau! O Jogo Terminou Empatado!\n");
                                        }
                                        else {
                                            printf("O Vencedor do Jogo Foi o Jogador %c!\n",vencedor);
                                            printa(e);
                                        }
                                        freeL(llig);
                                        llig = NULL;
                                        contaEstado = 0;
                                        contaEstadoBot = 0;
                                        printf("\nReversi > ");
                                    }
                                    else if (contaValidas == 0) {
                                        e = situacaoDeSkip(e);
                                        escondePontosBOT(e,nivel);
                                        e = jogadaBotMedium(e,nivel);
                                        llig = pushEstado(llig,e);
                                        printaBot(e,nivel);
                                        printf("\nReversi > ");
                                    }
                                    else {
                                        e = limpaPontos(e);
                                        printf("\nReversi > ");
                                    }
                                }
                                if (nivel == 3) {
                                    e = verificaLinha(e);
                                    e = verificaColuna(e);
                                    e = verificaDiagonal(e);
                                    contaValidas = contaJogadasValidas(e);
                                    if (situacaoDeSkipBOT(e) == 1) {
                                        printf("\nO Bot Não Tem Jogadas Disponíveis. É a Vez do Jogador Jogar.\n");
                                        e = trocaJogador(e);
                                        printaBot(e,nivel);
                                    }
                                    else {
                                        e = jogadaBotHard(e,nivel);
                                        e = trocaJogador(e);
                                        printaBot(e,nivel);
                                        llig = pushEstado(llig,e);
                                    }
                                    e = verificaLinha(e);
                                    e = verificaColuna(e);
                                    e = verificaDiagonal(e);
                                    contaValidas = contaJogadasValidas(e);
                                    if (fimDeJogo(e) == 1) {
                                        printf("\nNenhum dos Jogadores Têm Mais Jogadas Disponíveis. O Jogo Terminou!\n");
                                        vencedor = contaScore(e);
                                        if (vencedor == '?') {
                                            printf("\nUau! O Jogo Terminou Empatado!\n");
                                        }
                                        else {
                                            printf("O Vencedor do Jogo Foi o Jogador %c!\n",vencedor);
                                            printaBot(e,nivel);
                                        }
                                        freeL(llig);
                                        llig = NULL;
                                        contaEstado = 0;
                                        contaEstadoBot = 0;
                                        printf("\nReversi > ");
                                    }
                                    else if (contaValidas == 0) {
                                        e = situacaoDeSkip(e);
                                        escondePontosBOT(e,nivel);
                                        e = jogadaBotHard(e,nivel);
                                        e = trocaJogador(e);
                                        llig = pushEstado(llig,e);
                                        printaBot(e,nivel);
                                        printf("\nReversi > ");
                                    }
                                    else {
                                        e = limpaPontos(e);
                                        printf("\nReversi > ");
                                    }
                                }
                            }
                            else {
                                printf("\nA Jogada Não é Válida. Clique S ou H.\n");
                                printf("\nReversi > ");
                            }
                        }
                        else {
                            printf("\nOs Valores Inseridos São Inválidos.\n");
                            printf("\nReversi > ");
                        }
                    }
                    else {
                        printf("\nÉ Necessário Iniciar um Jogo Antes de Fazer uma Jogada.\n");
                        printf("\nReversi > ");
                    }
                }
                else {
                    printf("\nComando Inválido. Insira de Novo.\n");
                    printf("\nReversi > ");
                }
                for (i = 0; i < 200; i++) {
                    comando[i] = ' ';
                }
                comando[i] = '\0';
                break;
            }
            case 'S': {
                verifica = verificaSpaces(comando,1);
                if (verifica == 0) {
                    if (contaEstado != 0 && contaEstadoBot == 0) {
                        printf("\nAs Jogadas Válidas Estão Sinalizadas com o Ponto.\n");
                        e = verificaLinha(e);
                        e = verificaColuna(e);
                        e = verificaDiagonal(e);
                        printa(e);
                        printf("\nReversi > ");
                    }
                    else if (contaEstado == 0 && contaEstadoBot != 0) {
                        printf("\nAs Jogadas Válidas Estão Sinalizadas com o Ponto.\n");
                        e = verificaLinha(e);
                        e = verificaColuna(e);
                        e = verificaDiagonal(e);
                        printaBot(e,nivel);
                        printf("\nReversi > ");
                    }
                    else {
                        printf("\nÉ Necessário Iniciar um Jogo Antes de Ver as Jogadas Válidas.\n");
                        printf("\nReversi > ");
                    }
                }
                else {
                    printf("\nComando Inválido. Insira de Novo.\n");
                    printf("\nReversi > ");
                }
                for (i = 0; i < 200; i++) {
                    comando[i] = ' ';
                }
                comando[i] = '\0';
                break;
            }
            case 'H': {
                verifica = verificaSpaces(comando,1);
                if (verifica == 0) {
                    if (contaEstado != 0 && contaEstadoBot == 0) {
                        e = verificaLinha(e);
                        e = verificaColuna(e);
                        e = verificaDiagonal(e);
                        e = sugestaoAleatoria(e);
                        e = limpaPontos(e);
                        printa(e);
                        e = apagaSugestao(e);
                        printf("\nReversi > ");
                    }
                    else if (contaEstado == 0 && contaEstadoBot != 0) {
                        e = verificaLinha(e);
                        e = verificaColuna(e);
                        e = verificaDiagonal(e);
                        e = sugestaoAleatoria(e);
                        e = limpaPontos(e);
                        printaBot(e,nivel);
                        e = apagaSugestao(e);
                        printf("\nReversi > ");
                    }
                    else {
                        printf("\nÉ Necessário Iniciar um Jogo Antes de Obter uma Sugestão de Jogada.\n");
                        printf("\nReversi > ");
                    }
                }
                else {
                    printf("\nComando Inválido. Insira de Novo.\n");
                    printf("\nReversi > ");
                }
                for (i = 0; i < 200; i++) {
                    comando[i] = ' ';
                }
                comando[i] = '\0';
                break;
            }
            case 'U': {
                verifica = verificaSpaces(comando,1);
                if (verifica == 0) {
                    if (contaEstado != 0 && contaEstadoBot == 0) {
                        llig = popEstado(llig);
                        e = (llig -> estado);
                        printa(llig -> estado);
                        printf("\nReversi > ");
                    }
                    else if (contaEstado == 0 && contaEstadoBot != 0) {
                        llig = popEstadoBOT(llig);
                        if (llig -> next != NULL) {
                            llig = popEstadoBOTJogador(llig);
                            e = (llig -> estado);
                            printaBot((llig -> estado),nivel);
                            printf("\nReversi > ");
                        }
                        else {
                            e = (llig -> estado);
                            printaBot((llig -> estado),nivel);
                            printf("\nReversi > ");
                        }
                    }
                    else {
                        printf("\nÉ Necessário Iniciar um Jogo Antes de Executar o Comando UNDO.\n");
                        printf("\nReversi > ");
                    }
                }
                else {
                    printf("\nComando Inválido. Insira de Novo.\n");
                    printf("\nReversi > ");
                }
                for (i = 0; i < 200; i++) {
                    comando[i] = ' ';
                }
                comando[i] = '\0';
                break;
            }
            case 'A': {
                verifica = verificaSpaces(comando,5);
                if (verifica == 0 && isspace(comando[1]) && isspace(comando[3])) {
                    p = toupper(comando[2]);
                    if (p != 'X' && p != 'O') {
                        printf("\nPeça Inválida.\n");
                        printf("\nReversi > ");
                    }
                    else {
                        nivel = (int)(comando[4]);
                        nivel = nivel - 48;
                        if (nivel == 1 || nivel == 2 || nivel == 3) {
                            contaEstadoBot = contaEstadoBot + 1;
                            contaEstado = 0;
                            if (nivel == 1) {
                                if (p == 'O') {
                                    e.peca = VALOR_X;
                                    printf("\nBot Joga com 'O', Jogador Joga 'X'. O 'X' Começa Sempre Neste Modo de Jogo.\n");
                                    e.modo = 'A';
                                    e = mapaInicial(e);
                                    free(llig);
                                    llig = NULL;
                                    llig = pushEstado(llig,e);
                                    contaEstadoBot = contaEstadoBot + 1;
                                    printaBot(e,nivel);
                                    printf("\nReversi > ");
                                }
                                if (p == 'X') {
                                    e.peca = VALOR_X;
                                    e.modo = 'A';
                                    e = mapaInicial(e);
                                    free(llig);
                                    llig = NULL;
                                    llig = pushEstado(llig,e);
                                    contaEstadoBot = contaEstadoBot + 1;
                                    printaBot(e,nivel);
                                    e = jogadaBotEasy(e,nivel);
                                    llig = pushEstado(llig,e);
                                    printaBot(e,nivel);
                                    printf("\nReversi > ");
                                }
                            }
                            if (nivel == 2) {
                                if (p == 'O') {
                                    e.peca = VALOR_X;
                                    printf("\nBot Joga com 'O', Jogador Joga 'X'. O 'X' Começa Sempre Neste Modo de Jogo.\n");
                                    e.modo = 'A';
                                    e = mapaInicial(e);
                                    free(llig);
                                    llig = NULL;
                                    llig = pushEstado(llig,e);
                                    contaEstadoBot = contaEstadoBot + 1;
                                    printaBot(e,nivel);
                                    printf("\nReversi > ");
                                }
                                if (p == 'X') {
                                    e.peca = VALOR_X;
                                    e.modo = 'A';
                                    e = mapaInicial(e);
                                    free(llig);
                                    llig = NULL;
                                    llig = pushEstado(llig,e);
                                    contaEstadoBot = contaEstadoBot + 1;
                                    printaBot(e,nivel);
                                    e = jogadaBotMedium(e,nivel);
                                    llig = pushEstado(llig,e);
                                    printaBot(e,nivel);
                                    printf("\nReversi > ");
                                }
                            }
                            if (nivel == 3) {
                                if (p == 'O') {
                                    e.peca = VALOR_X;
                                    printf("\nBot Joga com 'O', Jogador Joga 'X'. O 'X' Começa Sempre Neste Modo de Jogo.\n");
                                    e.modo = 'A';
                                    e = mapaInicial(e);
                                    free(llig);
                                    llig = NULL;
                                    llig = pushEstado(llig,e);
                                    contaEstadoBot = contaEstadoBot + 1;
                                    printaBot(e,nivel);
                                    printf("\nReversi > ");
                                }
                                if (p == 'X') {
                                    e.peca = VALOR_X;
                                    e.modo = 'A';
                                    e = mapaInicial(e);
                                    free(llig);
                                    llig = NULL;
                                    llig = pushEstado(llig,e);
                                    contaEstadoBot = contaEstadoBot + 1;
                                    printaBot(e,nivel);
                                    e = jogadaBotHard(e,nivel);
                                    e = trocaJogador(e);
                                    llig = pushEstado(llig,e);
                                    printaBot(e,nivel);
                                    printf("\nReversi > ");
                                }
                            }
                        }
                        else {
                            printf("\nNível Inválido.\n");
                            printf("\nReversi > ");
                        }
                    }
                }
                else {
                    printf("\nComando Inválido. Insira de Novo.\n");
                    printf("\nReversi > ");
                }
                break;
            }
            case 'T': {
                verifica = verificaSpaces(comando,1);
                if (verifica == 0) {
                    menu();
                    printf("\n\nReversi > ");
                }
                else {
                    printf("\nComando Inválido. Insira de Novo.\n");
                    printf("\nReversi > ");
                }
                for (i = 0; i < 200; i++) {
                    comando[i] = ' ';
                }
                comando[i] = '\0';
                break;
            }
            case 'Q': {
                verifica = verificaSpaces(comando,1);
                if (verifica == 0) {
                    freeL(llig);
                    contaExit = contaExit + 1;
                }
                else {
                    printf("\nComando Inválido. Insira de Novo.\n");
                    printf("\nReversi > ");
                }
                break;
            }
            default: {
                contaComandos = contaComandos + 1;
                if (contaComandos > 1) {
                    printf("\nComando Inválido. Clique T Para Receber Ajuda.\n");
                    printf("\nReversi > ");
                    contaComandos = 0;
                }
                else {
                    printf("\nComando Inválido. Insira de Novo.\n");
                    printf("\nReversi > ");
                }
                break;
            }
        }
    }
}
