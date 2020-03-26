#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "estado.h"

/**
	Função que Cria o Mapa Inicial Colocando no Meio das Peças Iniciais.
*/

ESTADO mapaInicial (ESTADO e) {
    for (int l = 0; l < 8; l++) {
        for (int c = 0; c < 8; c++) {
            e.grelha[l][c] = VAZIA;
        }
    }
    e.grelha[3][4] = VALOR_X;
    e.grelha[4][3] = VALOR_X;
    e.grelha[3][3] = VALOR_O;
    e.grelha[4][4] = VALOR_O;
    return e;
}

/**
	Função que Imprime o Mapa Atual.
*/

void printa (ESTADO e) {
    char ch;
    putchar ('\n');
    if (e.peca == VALOR_X) {
        printf("%c X\n", e.modo);
    }
    if (e.peca == VALOR_O) {
        printf("%c O\n", e.modo);
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
	Função que Imprime o Mapa Atual sem os Pontos Correspondentes ao VALOR_S.
*/

void escondePontos (ESTADO e) {
    char ch;
    putchar ('\n');
    if (e.peca == VALOR_X) {
        printf("%c X\n", e.modo);
    }
    if (e.peca == VALOR_O) {
        printf("%c O\n", e.modo);
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
    imprimeArrayValidas(e);
    printf("\nScore:\nX = %d  O = %d\n", score(e,'X'), score(e,'O'));
}

/**
	Função que Apaga o VALOR_H do Estado de Jogo.
*/

ESTADO apagaSugestao (ESTADO e) {
    int l = 0;
    int c = 0;
    for (l = 0; l < 8; l++) {
        for (c = 0; c < 8; c++) {
            if ((e.grelha[l][c]) == VALOR_H) {
                e.grelha[l][c] = VAZIA;
            }
        }
    }
    return e;
}

/**
	Função que Imprime o Menu de Ajuda.
*/

void menu() {
    printf("\nN <Peça>         -> Novo Jogo. Começa o Jogador <Peça>");
    printf("\nL <Ficheiro>     -> Carregar Jogo Anterior");
    printf("\nE <Ficheiro>     -> Gravar Jogo Atual");
    printf("\nJ <L> <C>        -> Realizar uma Jogada");
    printf("\nS                -> Jogadas Válidas");
    printf("\nH                -> Obter uma Sugestão de Jogada");
    printf("\nA <Peça> <Nível> -> Novo Jogo Contra Bot. Bot Joga com <Peça>");
    printf("\nU                -> Undo");
    printf("\nQ                -> Sair");
}

/**
	Função que Carrega um Estado de Jogo Gravado em Ficheiro para um Estado Real.
*/

ESTADO loads (ESTADO e, char text []) {
    char ch;
    char p;
    FILE *f;
    if ((f = fopen (text, "r")) == NULL) {
        printf("\nO Ficheiro Inserido Não Existe.\n");
    }
    else {
        fscanf (f,"%c %c", &e.modo, &p);
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
	Função que Guarda o Estado Atual em Ficheiro.
*/

void saves (ESTADO e, char text[]) {
    char ch;
    FILE *f;
    f = fopen (text, "w");
    if (e.peca == VALOR_X) {
        fprintf(f,"%c X\n", e.modo);
    }
    if (e.peca == VALOR_O) {
        fprintf(f,"%c O\n", e.modo);
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
	Função que Elimina o VALOR_S do Estado Atual de Jogo.
*/

ESTADO limpaPontos (ESTADO e) {
    for (int l = 0; l < 8; l++) {
        for (int c = 0; c < 8; c++) {
            if (e.grelha[l][c] == VALOR_S) {
                e.grelha[l][c] = VAZIA;
            }
        }
    }
    return e;
}

/**
	Função que Conta o Número de Jogadas Válidas Dísponíveis Para o Jogador Atual.
*/

int contaJogadasValidas (ESTADO e) {
    int l = 0;
    int c = 0;
    int contador = 0;
    for (l = 0; l < 8; l++) {
        for (c = 0; c < 8; c++) {
            if (e.grelha[l][c] == VALOR_S) {
                contador++;
            }
        }
    }
    return contador;
}

/**
	Função que Troca o Jogador.
*/

ESTADO trocaJogador (ESTADO e) {
    if (e.peca == VALOR_X) {
        e.peca = VALOR_O;
        printf("\nO Próximo Jogador a Jogar é o Jogador com a Peça Bola.\n");
    }
    else {
        e.peca = VALOR_X;
        printf("\nO Próximo Jogador a Jogar é o Jogador com a Peça Cruz.\n");
    }
    return e;
}

/**
	Função que Conta o Score dos Dois Jogadores.
*/

int score (ESTADO e, char p) {
    int X = 0;
    int O = 0;
    int r = 0;
    for (int l = 0; l < 8; l++) {
        for (int c = 0; c < 8; c++) {
            if (e.grelha[l][c] == VALOR_O) {
                O = O + 1;
            }
            if (e.grelha[l][c] == VALOR_X) {
                X = X + 1;
            }
        }
    }
    if (p == 'O') {
        r = O;
    }
    if (p == 'X') {
        r = X;
    }
    return r;
}

/**
	Função que Acrescenta o Estado Resultante de uma Jogada à Lista Ligada.
*/

LL pushEstado (LL llig, ESTADO e) {
    LL new = malloc (sizeof(struct listaL));
    new -> estado = e;
    new -> next = llig;
    return new;
}

/**
	Função UNDO.
*/

LL popEstado (LL llig) {
    LL l2 = llig;
    if (l2 -> next == NULL) {
        printf("\nNão é Possível Voltar Mais Atrás. O Jogo Já se Encontra no Estado Inicial.\n");
    }
    else {
        l2 = l2 -> next;
        free(llig);
        llig = l2;
        printf("\nIrá Regressar uma Jogada Atrás\n");
    }
    return llig;
}

/**
	Função que Liberta Todo o Espaço Ocupado por uma Lista Ligada No Final do Jogo.
*/

void freeL (LL llig) {
    LL anterior;
    while (llig != NULL) {
        anterior = llig;
        llig = llig -> next;
        free(anterior);
    }
}

/**
	Função que Gera uma Jogada Aleatória.
*/

ESTADO sugestaoAleatoria (ESTADO e) {
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
                    printf("\nUma Jogada Possível Pode Ser Realizada na Linha %d e Coluna %d!\n", l, c);
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
	Função que Verifica se Existe uma Situação de Skip.
	Em Caso Afirmativo, Troca o Jogador.
*/

ESTADO situacaoDeSkip (ESTADO e) {
    int contagem = 0;
    contagem = contaJogadasValidas(e);
    if (contagem == 0) {
        printf("\nO Jogador Não Tem Jogadas Disponíveis. É a Vez do Próximo Jogador Jogar.\n");
        e = trocaJogador(e);
    }
    else {
        return e;
    }
    return e;
}

/**
	Função que Verifica se um Jogo Acabou.
*/

int fimDeJogo (ESTADO e) {
    int flag = 0;
    int contagem = 0;
    contagem = contaJogadasValidas(e);
    if (contagem == 0) {
        flag = flag + 1;
    }
    if (e.peca == VALOR_X) {
        e.peca = VALOR_O;
    }
    else {
        e.peca = VALOR_X;
    }
    e = verificaLinha(e);
    e = verificaColuna(e);
    e = verificaDiagonal(e);
    contagem = contaJogadasValidas(e);
    if (contagem == 0) {
        flag = flag + 1;
    }
    if (flag == 2) {
        return 1;
    }
    else {
        return 0;
    }
}

/**
	Função que Conta o Score de Cada Jogador e Declara um Vencedor.
*/

char contaScore (ESTADO e) {
    char vencedor = 'W';
    int l = 0;
    int c = 0;
    int contaCruz = 0;
    int contaBola = 0;
    for (l = 0; l < 8; l++) {
        for (c = 0; c < 8; c++) {
            if (e.grelha[l][c] == VALOR_X) {
                contaCruz = contaCruz + 1;
            }
            if (e.grelha[l][c] == VALOR_O) {
                contaBola = contaBola + 1;
            }
        }
    }
    if (contaCruz > contaBola) {
        vencedor = 'X';
    }
    if (contaCruz < contaBola) {
        vencedor = 'O';
    }
    if (contaCruz == contaBola) {
        vencedor = '?';
    }
    return vencedor;
}

/**
	Função que Extrai o Modo de Jogo, de um Jogo Gravado em Ficheiro de Texto.
*/

int extraiModo (char text[100]) {
    char ch;
    FILE *f;
    f = fopen (text, "r");
    fscanf(f,"%c", &ch);
    if (ch == 'M') {
        return 0;
    }
    else {
        return 1;
    }
    fclose(f);
}

/**
	Função que Imprime uma Lista com as Jogadas Válidas que o Jogador Atual Possuí.
*/

void imprimeArrayValidas (ESTADO e) {
    int l = 0;
    int c = 0;
    int contaValidas = 0;
    e = verificaLinha(e);
    e = verificaColuna(e);
    e = verificaDiagonal(e);
    contaValidas = contaJogadasValidas(e);
    if (contaValidas == 0) {
        printf("\nO Jogador Não Tem Jogadas Válidas\n");
    }
    else {
        printf("\nJogadas Válidas: ");
        for (l = 0; l < 8; l++) {
            for (c = 0; c < 8; c++) {
                if (e.grelha[l][c] == VALOR_S) {
                    printf("[%d,",l);
                    printf("%d]",c);
                    printf(" ");
                }
            }
        }
    }
}