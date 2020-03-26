#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "estado.h"

/**
    Função que Executa uma Jogada do Bot Nível 1.
*/

ESTADO jogadaBotEasy (ESTADO e, int x) {
    int l = 0;
    int c = 0;
    int l1 = 0;
    int c1 = 0;
    e = verificaLinha(e);
    e = verificaColuna(e);
    e = verificaDiagonal(e);
    if (situacaoDeSkipBOT(e) == 1) {
        printf("\nO Bot Não Tem Jogadas Disponíveis. É a Vez do Jogador Jogar.\n");
        e = trocaJogador(e);
    }
    else {
        e = sugestaoAleatoriaBOT(e);
        e = limpaPontos(e);
        for (l = 0; l < 8; l++) {
            for (c = 0; c < 8; c++) {
                if (e.grelha[l][c] == VALOR_H) {
                    l1 = l;
                    c1 = c;
                }
            }
        }
        e = converte(e,l1,c1);
        e = apagaSugestao(e);
        printaBot(e,x);
        e = trocaJogador(e);
    }
    return e;
}

/**
    Função que Imprime o Mapa Atual em Modo A.
*/

void printaBot (ESTADO e, int x) {
    char ch;
    putchar ('\n');
    if (e.peca == VALOR_X) {
        printf("A X %d\n", x);
    }
    if (e.peca == VALOR_O) {
        printf("A O %d\n", x);
    }
    printf("♫ 0 1 2 3 4 5 6 7\n");
    for (int l = 0; l < 8; l++) {
        printf("%d ", l);
        for (int c = 0; c < 8; c++) {
            switch (e.grelha[l][c]) {
                case VALOR_O: {
                    ch = 'O';
                    break;
                }
                case VALOR_S : {
                    ch = '.';
                    break;
                }
                case VALOR_X : {
                    ch = 'X';
                    break;
                }
                case VALOR_H : {
                    ch = '?';
                    break;
                }
                case VAZIA: {
                    ch = '-';
                    break;
                }
            }
            printf("%c ", ch);
        }
        printf("\n");
    }
    imprimeArrayValidas(e);
    printf("\nScore:\nX = %d  O = %d\n", score(e,'X'), score(e,'O'));
}

/**
    Função que Gera uma Jogada Aleatória Para o Bot Nível 1.
*/

ESTADO sugestaoAleatoriaBOT (ESTADO e) {
    int l = 0;
    int c = 0;
    int begin = 0;
    int contagem = 0;
    int aleatorio = 0;
    srand(time(NULL));
    contagem = contaJogadasValidas(e);
    aleatorio = (rand () % contagem);
    for (l = 0; l < 8; l++) {
        for (c = 0; c < 8; c++) {
            if (e.grelha[l][c] == VALOR_S) {
                if (begin == aleatorio) {
                    e.grelha[l][c] = VALOR_H;
                    printf("\nO Bot Jogou na Linha %d e Coluna %d!\n", l, c);
                    begin = 100;
                }
                else {
                    begin = begin + 1;
                }
            }
        }
    }
    return e;
}

/**
    Função UNDO do Bot.
*/

LL popEstadoBOT (LL llig) {
    LL l2 = llig;
    if (l2 -> next == NULL) {
        printf("\nNão é Possível Voltar Mais Atrás. O Jogo Já se Encontra no Estado Inicial.\n");
    }
    else {
        l2 = l2 -> next;
        free(llig);
        llig = l2;
        printf("\nA Jogada do Bot Irá Ser Cancelada.\n");
    }
    return llig;
}

/**
    Função UNDO do Bot, que Retira Duas Jogadas ao Estado, a do Jogador Atual e a do Bot.
*/

LL popEstadoBOTJogador (LL llig) {
    LL l2 = llig;
    if (l2 -> next == NULL) {
        printf("\nNão é Possível Voltar Mais Atrás. O Jogo Já se Encontra no Estado Inicial.\n");
    }
    else {
        l2 = l2 -> next;
        free(llig);
        llig = l2;
        printf("\nA Sua Jogada Irá Ser Cancelada.\n");
    }
    return llig;
}

/**
    Função que Verifica se Existe uma Situação de Skip do Bot.
*/

int situacaoDeSkipBOT (ESTADO e) {
    int contagem = 0;
    contagem = contaJogadasValidas(e);
    if (contagem == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

/**
    Função que Grava um Estado de Jogo em Modo A.
*/

void savesBOT (ESTADO e, char text[], int x) {
    char ch;
    FILE *f;
    f = fopen (text, "w");
    if (e.peca == VALOR_X) {
        fprintf(f,"%c X %d\n", e.modo, x);
    }
    if (e.peca == VALOR_O) {
        fprintf(f,"%c O %d\n", e.modo, x);
    }
    for (int l = 0; l < 8; l++) {
        for (int c = 0; c < 8; c++) {
            if (e.grelha[l][c] == VAZIA) {
                ch = '-';
                fprintf(f, "%c ", ch);
            }
            if (e.grelha[l][c] == VALOR_O) {
                ch = 'O';
                fprintf(f, "%c ", ch);
            }
            if (e.grelha[l][c] == VALOR_X) {
                ch = 'X';
                fprintf(f, "%c ", ch);
            }
            if (e.grelha[l][c] == VALOR_S) {
                ch = '.';
                fprintf(f, "%c ", ch);
            }
        }
        fprintf(f,"\n");
    }
    fclose(f);
}

/**
    Função que Carrega de um Ficheiro, um Estado de Jogo em Modo A.
*/

ESTADO loadsBOT (ESTADO e, char text []) {
    char ch;
    char p;
    int nivel;
    FILE *f;
    if ((f = fopen (text, "r")) == NULL) {
        printf("\nO Ficheiro Inserido Não Existe.\n");
    }
    else {
        fscanf (f,"%c %c %d", &e.modo, &p, &nivel);
        if (p == 'X') {
            e.peca = VALOR_X;
        }
        if (p == 'O') {
            e.peca = VALOR_O;
        }
        for (int l = 0; l < 8; l++) {
            for (int c = 0; c < 8; c++) {
                fscanf(f, " %c", &ch);
                if (ch == '-') {
                    e.grelha[l][c] = VAZIA;
                }
                if (ch == 'X') {
                    e.grelha[l][c] = VALOR_X;
                }
                if (ch == 'O') {
                    e.grelha[l][c] = VALOR_O;
                }
                if (ch == '.') {
                    e.grelha[l][c] = VALOR_S;
                }
            }
        }
        fclose(f);
    }
    return e;
}

/**
    Função que Extrai de um Ficheiro o Nível em que o Bot está a Jogar.
*/

int extraiNivel (char text[100]) {
    char ch;
    char p;
    int nivel;
    FILE *f;
    f = fopen (text, "r");
    fscanf (f,"%c %c %d",&ch, &p, &nivel);
    fclose(f);
    return nivel;
}

/**
    Função que Atribui a Cada Casa do Tabuleiro um Valor Imaginário.
    Esses Valores Correspondem ao Benefício que o Jogador tem por Possuír Essa Casa.
    Por Exemplo, os Cantos são as Posições Mais Valiosas Porque é Impossível o Adversário Colocar uma Peça lá.
*/

int valorTabuleiro (int l, int c) {
    int value = 0;
    if ((l == 0 && c == 0) || (l == 0 && c == 7) || (l == 7 && c == 0) || (l == 7 && c == 7)) {
        value = 10000;
    }
    if ((l == 0 && c == 1) || (l == 0 && c == 6) || (l == 1 && c == 0) || (l == 1 && c == 7) || (l == 6 && c == 0) || (l == 6 && c == 7) || (l == 7 && c == 1) || (l == 7 && c == 6)) {
        value = (-3000);
    }
    if ((l == 0 && c == 2) || (l == 0 && c == 5) || (l == 2 && c == 0) || (l == 2 && c == 7) || (l == 5 && c == 0) || (l == 5 && c == 7) || (l == 7 && c == 2) || (l == 7 && c == 5)) {
        value = 1000;
    }
    if ((l == 0 && c == 3) || (l == 0 && c == 4) || (l == 3 && c == 0) || (l == 3 && c == 7) || (l == 4 && c == 0) || (l == 4 && c == 7) || (l == 7 && c == 3) || (l == 7 && c == 4)) {
        value = 800;
    }
    if ((l == 1 && c == 1) || (l == 1 && c == 6) || (l == 6 && c == 1) || (l == 6 && c == 6)) {
        value = (-5000);
    }
    if ((l == 1 && c == 2) || (l == 1 && c == 5) || (l == 2 && c == 1) || (l == 2 && c == 6) || (l == 5 && c == 1) || (l == 5 && c == 6) || (l == 6 && c == 2) || (l == 6 && c == 5)) {
        value = (-450);
    }
    if ((l == 1 && c == 3) || (l == 1 && c == 4) || (l == 3 && c == 1) || (l == 3 && c == 6) || (l == 4 && c == 1) || (l == 4 && c == 6) || (l == 6 && c == 3) || (l == 6 && c == 4)) {
        value = (-500);
    }
    if ((l == 2 && c == 2) || (l == 2 && c == 5) || (l == 5 && c == 2) || (l == 5 && c == 5)) {
        value = 30;
    }
    if ((l == 3 && c == 3) || (l == 3 && c == 4) || (l == 4 && c == 3) || (l == 4 && c == 4)) {
        value = 50;
    }
    if ((l == 2 && c == 3) || (l == 2 && c == 4) || (l == 3 && c == 2) || (l == 3 && c == 5) || (l == 4 && c == 2) || (l == 4 && c == 5) || (l == 5 && c == 3) || (l == 5 && c == 4)) {
        value = 10;
    }
    return value;
}

/**
    Função que Extrai o Índice do Maior Elemento de um Array.
*/

int maiorIndiceArray (int value[100], int x) {
    int i = 1;
    int maior = value[0];
    int indice = 0;
    while (i < x) {
        if (value[i] > maior) {
            maior = value[i];
            indice = i;
            i++;
        }
        else {
            i++;
        }
    }
    return indice;
}

/**
    Função que Extrai o Maior Elemento de um Array.
*/

int maiorElementoArray (int value[100], int x) {
    int i = 1;
    int maior = value[0];
    while (i < x) {
        if (value[i] >= maior) {
            maior = value[i];
            i++;
        }
        else {
            i++;
        }
    }
    return maior;
}

/**
    Função que Remove um Elemento de um Array.
*/

int removeElement (int value[100], int n, int p) {
    int i = 0;
    for (i = p - 1; i < n - 1; i++) {
        value[i] = value[i + 1];
    }
    return (n - 1);
}

/**
    Função Executa a Jogada de um Bot Nível 2.
*/

ESTADO jogadaBotMedium (ESTADO e, int x) {
    int l = 0;
    int c = 0;
    int l1 = 0;
    int c1 = 0;
    int s[100];
    int value[100];
    int contador = 0;
    int index = 0;
    int contaValidas = 0;
    int counter = 0;
    int maiorTabuleiro = 0;
    e = verificaLinha(e);
    e = verificaColuna(e);
    e = verificaDiagonal(e);
    if (situacaoDeSkipBOT(e) == 1) {
        printf("\nO Bot Não Tem Jogadas Disponíveis. É a Vez do Jogador Jogar.\n");
        e = trocaJogador(e);
    }
    else {
        contaValidas = contaJogadasValidas(e);
        for (l = 0; l < 8; l++) {
            for (c = 0; c < 8; c++) {
                if (e.grelha[l][c] == VALOR_S) {
                    s[contador] = l;
                    contador = contador + 1;
                    s[contador] = c;
                    contador = contador + 1;
                }
            }
        }
        contador = 0;
        while (counter != contaValidas) {
            value[index] = valorTabuleiro(s[contador],s[contador + 1]);
            contador = contador + 2;
            counter = counter + 1;
            index = index + 1;
        }
        maiorTabuleiro = maiorIndiceArray(value,index);
        l1 = s[maiorTabuleiro + maiorTabuleiro];
        maiorTabuleiro = maiorTabuleiro + maiorTabuleiro;
        c1 = s[maiorTabuleiro + 1];
        e = converte(e,l1,c1);
        e = limpaPontos(e);
        printf("\nO Bot Jogou na Linha %d e Coluna %d!\n", l1, c1);
        printaBot(e,x);
        e = trocaJogador(e);
    }
    return e;
}

/**
    Função que Executa uma Jogada de um Bot Nível 3.
*/

ESTADO jogadaBotHard (ESTADO e, int x) {
    int l = 0;
    int c = 0;
    int i = 0;
    int z = 0;
    int tamanho = 0;
    int valores[100];
    int resultado[100];
    int melhorIndice = 0;
    int segundoIndice = 0;
    int melhorResultado = 0;
    int segundoResultado = 0;
    int melhorLinha = 0;
    int melhorColuna = 0;
    int segundaMelhorLinha = 0;
    int segundaMelhorColuna = 0;
    int melhorJogadaJogador = 0;
    int segundaMelhorJogadaJogador = 0;
    ESTADO e1;
    ESTADO e2;
    e = verificaLinha(e);
    e = verificaColuna(e);
    e = verificaDiagonal(e);
    for (l = 0; l < 8; l++) {
        for (c = 0; c < 8; c++) {
            if (e.grelha[l][c] == VALOR_S) {
                resultado[i] = l;
                i++;
                resultado[i] = c;
                i++;
                valores[z] = valorTabuleiro(l,c);
                z++;
            }
        }
    }
    melhorResultado = maiorElementoArray(valores,z);
    melhorIndice = maiorIndiceArray(valores,z);
    melhorLinha = resultado[melhorIndice + melhorIndice];
    melhorColuna = resultado[melhorIndice + melhorIndice + 1];
    if (z > 1) {
        z = removeElement(valores,z,maiorIndiceArray(valores,z));
        i = removeElement(resultado,i,(resultado[melhorIndice + melhorIndice]));
        i = removeElement(resultado,i,(resultado[melhorIndice + melhorIndice + 1]));
        segundoResultado = maiorElementoArray(valores,z);
        segundoIndice = maiorIndiceArray(valores,z);
        segundaMelhorLinha = resultado[segundoIndice + segundoIndice];
        segundaMelhorColuna = resultado[segundoIndice + segundoIndice + 1];
        e2 = converte(e,segundaMelhorLinha,segundaMelhorColuna);
        i = 0;
        z = 0;
        e2 = verificaLinha(e2);
        e2 = verificaColuna(e2);
        e2 = verificaDiagonal(e2);
        for (l = 0; l < 8; l++) {
            for (c = 0; c < 8; c++) {
                if (e.grelha[l][c] == VALOR_S) {
                    valores[i] = valorTabuleiro(l,c);
                    i++;
                }
            }
        }
        if (i == 0) {
            segundaMelhorJogadaJogador = (-20000);
        }
        else {
            segundaMelhorJogadaJogador = maiorElementoArray(valores,i);
        }
    }
    e1 = converte(e,melhorLinha,melhorColuna);
    e1 = verificaLinha(e1);
    e1 = verificaColuna(e1);
    e1 = verificaDiagonal(e1);
    i = 0;
    z = 0;
    for (l = 0; l < 8; l++) {
        for (c = 0; c < 8; c++) {
            if (e.grelha[l][c] == VALOR_S) {
                valores[i] = valorTabuleiro(l,c);
                i++;
            }
        }
    }
    if (i == 0) {
        melhorJogadaJogador = (-20000);
    }
    else {
        melhorJogadaJogador = maiorElementoArray(valores,i);
    }
    if ((melhorResultado - melhorJogadaJogador) >= (segundoResultado - segundaMelhorJogadaJogador)) {
        printf("\nO Bot Jogou na Linha %d e Coluna %d!\n", melhorLinha, melhorColuna);
        e = converte(e,melhorLinha,melhorColuna);
        e = limpaPontos(e);
        printaBot(e,x);
    }
    else {
        printf("\nO Bot Jogou na Linha %d e Coluna %d!\n", segundaMelhorLinha, segundaMelhorColuna);
        e = converte(e,segundaMelhorLinha,segundaMelhorColuna);
        e = limpaPontos(e);
        printaBot(e,x);
    }
    return e;
}

/**
    Função que Imprime o Mapa de Jogo Atual sem os VALOR_S.
*/

void escondePontosBOT (ESTADO e, int x) {
    char ch;
    putchar ('\n');
    if (e.peca == VALOR_X) {
        printf("A X %d\n", x);
    }
    if (e.peca == VALOR_O) {
        printf("A O %d\n", x);
    }
    printf("♫ 0 1 2 3 4 5 6 7\n");
    for (int l = 0; l < 8; l++) {
        printf("%d ", l);
        for (int c = 0; c < 8; c++) {
            switch (e.grelha[l][c]) {
                case VALOR_O: {
                    ch = 'O';
                    break;
                }
                case VALOR_S : {
                    ch = '-';
                    break;
                }
                case VALOR_X : {
                    ch = 'X';
                    break;
                }
                case VALOR_H : {
                    ch = '?';
                    break;
                }
                case VAZIA: {
                    ch = '-';
                    break;
                }
            }
            printf("%c ", ch);
        }
        printf("\n");
    }
    printf("\nScore:\nX = %d  O = %d\n", score(e,'X'), score(e,'O'));
}