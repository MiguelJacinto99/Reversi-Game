#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "estado.h"

/**
	Função que Coloca um Sinalizador no Lugar Onde a Jogada é Válida. Apenas Para Movimentos Horizontais.
*/

ESTADO verificaLinha (ESTADO e) {
    int l, c;
    int l1, c1 = 0;
    int contador;
    if (e.peca == VALOR_X) {
        for (l = 0; l < 8; l++) {
            for (c = 0; c < 8; c++) {
                if (e.grelha[l][c] == VALOR_X) {
                    contador = 0;
                    l1 = l;
                    c1 = c;
                    while (e.grelha[l][c - 1] == VALOR_O && (c - 1) >= 0 && (c - 1) < 8) {
                        c--;
                        contador++;
                    }
                    if (contador > 0) {
                        c--;
                        if (c >= 0 && c < 8 && e.grelha[l][c] != VALOR_X) {
                            e.grelha[l][c] = VALOR_S;
                        }
                    }
                    l = l1;
                    c = c1;
                    contador = 0;
                    while (e.grelha[l][c + 1] == VALOR_O && (c + 1) >= 0 && (c + 1) < 8) {
                        c++;
                        contador++;
                    }
                    if (contador > 0) {
                        c++;
                        if (c >= 0 && c < 8 && e.grelha[l][c] != VALOR_X) {
                            e.grelha[l][c] = VALOR_S;
                        }
                    }
                    l = l1;
                    c = c1;
                }
            }
        }
    }
    if (e.peca == VALOR_O) {
        for (l = 0; l < 8; l++) {
            for (c = 0; c < 8; c++) {
                if (e.grelha[l][c] == VALOR_O) {
                    contador = 0;
                    l1 = l;
                    c1 = c;
                    while (e.grelha[l][c - 1] == VALOR_X && (c - 1) >= 0 && (c - 1) < 8) {
                        c--;
                        contador++;
                    }
                    if (contador > 0) {
                        c--;
                        if (c >= 0 && c < 8 && e.grelha[l][c] != VALOR_O) {
                            e.grelha[l][c] = VALOR_S;
                        }
                    }
                    l = l1;
                    c = c1;
                    contador = 0;
                    while (e.grelha[l][c + 1] == VALOR_X && (c + 1) >= 0 && (c + 1) < 8) {
                        c++;
                        contador++;
                    }
                    if (contador > 0) {
                        c++;
                        if (c >= 0 && c < 8 && e.grelha[l][c] != VALOR_O) {
                            e.grelha[l][c] = VALOR_S;
                        }
                    }
                    l = l1;
                    c = c1;
                }
            }
        }
    }
    return e;
}

/**
	Função que Coloca um Sinalizador no Lugar Onde a Jogada é Válida. Apenas Para Movimentos Verticais.
*/

ESTADO verificaColuna (ESTADO e) {
    int l, c;
    int l1, c1 = 0;
    int contador;
    if (e.peca == VALOR_X) {
        for (l = 0; l < 8; l++) {
            for (c = 0; c < 8; c++) {
                if (e.grelha[l][c] == VALOR_X) {
                    contador = 0;
                    l1 = l;
                    c1 = c;
                    while (e.grelha[l - 1][c] == VALOR_O && (l - 1) >= 0 && (l - 1) < 8) {
                        l--;
                        contador++;
                    }
                    if (contador > 0) {
                        l--;
                        if (l >= 0 && l < 8 && e.grelha[l][c] != VALOR_X) {
                            e.grelha[l][c] = VALOR_S;
                        }
                    }
                    l = l1;
                    c = c1;
                    contador = 0;
                    while (e.grelha[l + 1][c] == VALOR_O && (l + 1) >= 0 && (l + 1) < 8) {
                        l++;
                        contador++;
                    }
                    if (contador > 0) {
                        l++;
                        if (l >= 0 && l < 8 && e.grelha[l][c] != VALOR_X) {
                            e.grelha[l][c] = VALOR_S;
                        }
                    }
                    l = l1;
                    c = c1;
                }
            }
        }
    }
    if (e.peca == VALOR_O) {
        for (l = 0; l < 8; l++) {
            for (c = 0; c < 8; c++) {
                if (e.grelha[l][c] == VALOR_O) {
                    contador = 0;
                    l1 = l;
                    c1 = c;
                    while (e.grelha[l - 1][c] == VALOR_X && (l - 1) >= 0 && (l - 1) < 8) {
                        l--;
                        contador++;
                    }
                    if (contador > 0) {
                        l--;
                        if (l >= 0 && l < 8 && e.grelha[l][c] != VALOR_O) {
                            e.grelha[l][c] = VALOR_S;
                        }
                    }
                    l = l1;
                    c = c1;
                    contador = 0;
                    while (e.grelha[l + 1][c] == VALOR_X && (l + 1) >= 0 && (l + 1) < 8) {
                        l++;
                        contador++;
                    }
                    if (contador > 0) {
                        l++;
                        if (l >= 0 && l < 8 && e.grelha[l][c] != VALOR_O) {
                            e.grelha[l][c] = VALOR_S;
                        }
                    }
                    l = l1;
                    c = c1;
                }
            }
        }
    }
    return e;
}

/**
	Função que Coloca um Sinalizador no Lugar Onde a Jogada é Válida. Apenas Para Movimentos Diagonais.
*/

ESTADO verificaDiagonal (ESTADO e) {
    int l, c;
    int l1, c1 = 0;
    int contador;
    if (e.peca == VALOR_X) {
        for (l = 0; l < 8; l++) {
            for (c = 0; c < 8; c++) {
                if (e.grelha[l][c] == VALOR_X) {
                    contador = 0;
                    l1 = l;
                    c1 = c;
                    while (e.grelha[l - 1][c - 1] == VALOR_O && (l - 1) >= 0 && (c - 1) >= 0 && (l - 1) < 8 && (c - 1) < 8) {
                        l--;
                        c--;
                        contador++;
                    }
                    if (contador > 0) {
                        l--;
                        c--;
                        if (l >= 0 && c >= 0 && l < 8 && c < 8 && e.grelha[l][c] != VALOR_X) {
                            e.grelha[l][c] = VALOR_S;
                        }
                    }
                    l = l1;
                    c = c1;
                    contador = 0;
                    while (e.grelha[l + 1][c + 1] == VALOR_O && (l + 1) >= 0 && (c + 1) >= 0 && (l + 1) < 8 && (c + 1) < 8) {
                        l++;
                        c++;
                        contador++;
                    }
                    if (contador > 0) {
                        l++;
                        c++;
                        if (l >= 0 && c >= 0 && l < 8 && c < 8 && e.grelha[l][c] != VALOR_X) {
                            e.grelha[l][c] = VALOR_S;
                        }
                    }
                    l = l1;
                    c = c1;
                    contador = 0;
                    while (e.grelha[l - 1][c + 1] == VALOR_O && (l - 1) >= 0 && (c + 1) >= 0 && (l - 1) < 8 && (c + 1) < 8) {
                        l--;
                        c++;
                        contador++;
                    }
                    if (contador > 0) {
                        l--;
                        c++;
                        if (l >= 0 && c >= 0 && l < 8 && c < 8 && e.grelha[l][c] != VALOR_X) {
                            e.grelha[l][c] = VALOR_S;
                        }
                    }
                    l = l1;
                    c = c1;
                    contador = 0;
                    while (e.grelha[l + 1][c - 1] == VALOR_O && (l + 1) >= 0 && (c - 1) >= 0 && (l + 1) < 8 && (c - 1) < 8) {
                        l++;
                        c--;
                        contador++;
                    }
                    if (contador > 0) {
                        l++;
                        c--;
                        if (l >= 0 && c >= 0 && l < 8 && c < 8 && e.grelha[l][c] != VALOR_X) {
                            e.grelha[l][c] = VALOR_S;
                        }
                    }
                    l = l1;
                    c = c1;
                }
            }
        }
    }
    if (e.peca == VALOR_O) {
        for (l = 0; l < 8; l++) {
            for (c = 0; c < 8; c++) {
                if (e.grelha[l][c] == VALOR_O) {
                    contador = 0;
                    l1 = l;
                    c1 = c;
                    while (e.grelha[l - 1][c - 1] == VALOR_X && (l - 1) >= 0 && (c - 1) >= 0 && (l - 1) < 8 && (c - 1) < 8) {
                        l--;
                        c--;
                        contador++;
                    }
                    if (contador > 0) {
                        l--;
                        c--;
                        if (l >= 0 && c >= 0 && l < 8 && c < 8 && e.grelha[l][c] != VALOR_O) {
                            e.grelha[l][c] = VALOR_S;
                        }
                    }
                    l = l1;
                    c = c1;
                    contador = 0;
                    while (e.grelha[l + 1][c + 1] == VALOR_X && (l + 1) >= 0 && (c + 1) >= 0 && (l + 1) < 8 && (c + 1) < 8) {
                        l++;
                        c++;
                        contador++;
                    }
                    if (contador > 0) {
                        l++;
                        c++;
                        if (l >= 0 && c >= 0 && l < 8 && c < 8 && e.grelha[l][c] != VALOR_O) {
                            e.grelha[l][c] = VALOR_S;
                        }
                    }
                    l = l1;
                    c = c1;
                    contador = 0;
                    while (e.grelha[l - 1][c + 1] == VALOR_X && (l - 1) >= 0 && (c + 1) >= 0 && (l - 1) < 8 && (c + 1) < 8) {
                        l--;
                        c++;
                        contador++;
                    }
                    if (contador > 0) {
                        l--;
                        c++;
                        if (l >= 0 && c >= 0 && l < 8 && c < 8 && e.grelha[l][c] != VALOR_O) {
                            e.grelha[l][c] = VALOR_S;
                        }
                    }
                    l = l1;
                    c = c1;
                    contador = 0;
                    while (e.grelha[l + 1][c - 1] == VALOR_X && (l + 1) >= 0 && (c - 1) >= 0 && (l + 1) < 8 && (c - 1) < 8) {
                        l++;
                        c--;
                        contador++;
                    }
                    if (contador > 0) {
                        l++;
                        c--;
                        if (l >= 0 && c >= 0 && l < 8 && c < 8 && e.grelha[l][c] != VALOR_O) {
                            e.grelha[l][c] = VALOR_S;
                        }
                    }
                    l = l1;
                    c = c1;
                }
            }
        }
    }
    return e;
}

/**
	Função que Converte as Peças do Adversário Após a Realização de uma Jogada. Para Todo o Tipo de Movimentos.
*/

ESTADO converte (ESTADO e, int l, int c) {
    int s[100];
    int i = 0;
    int contador = 0;
    int l1, c1 = 0;
    if (e.peca == VALOR_X) {
        l1 = l;
        c1 = c;
        contador = 0;
        while (e.grelha[l - 1][c] == VALOR_O && (existeColunaCima(e,l1,c1) == 1) && (l - 1) >= 0 && c >= 0 && (l - 1) < 8 && c < 8) {
            s[contador] = (l - 1);
            contador++;
            s[contador] = c;
            contador++;
            l--;
        }
        l = l1;
        while (e.grelha[l + 1][c] == VALOR_O && (existeColunaBaixo(e,l1,c1) == 1) && (l + 1) >= 0 && c >= 0 && (l + 1) < 8 && c < 8) {
            s[contador] = (l + 1);
            contador++;
            s[contador] = c;
            contador++;
            l++;
        }
        l = l1;
        while (e.grelha[l][c - 1] == VALOR_O && (existeLinhaEsquerda(e,l1,c1) == 1) && l >= 0 && (c - 1) >= 0 && l < 8 && (c - 1) < 8) {
            s[contador] = l;
            contador++;
            s[contador] = (c - 1);
            contador++;
            c--;
        }
        c = c1;
        while (e.grelha[l][c + 1] == VALOR_O && (existeLinhaDireita(e,l1,c1) == 1) && l >= 0 && (c + 1) >= 0 && l < 8 && (c + 1) < 8) {
            s[contador] = l;
            contador++;
            s[contador] = (c + 1);
            contador++;
            c++;
        }
        c = c1;
        while (e.grelha[l - 1][c - 1] == VALOR_O && (existeDiagonalEsquerda(e,l1,c1) == 1) && (l - 1) >= 0 && (c - 1) >= 0 && (l - 1) < 8 && (c - 1) < 8) {
            s[contador] = (l - 1);
            contador++;
            s[contador] = (c - 1);
            contador++;
            l--;
            c--;
        }
        l = l1;
        c = c1;
        while (e.grelha[l + 1][c + 1] == VALOR_O && (existeDiagonalDireita(e,l1,c1) == 1) && (l + 1) >= 0 && (c + 1) >= 0 && (l + 1) < 8 && (c + 1) < 8) {
            s[contador] = (l + 1);
            contador++;
            s[contador] = (c + 1);
            contador++;
            l++;
            c++;
        }
        l = l1;
        c = c1;
        while (e.grelha[l - 1][c + 1] == VALOR_O && (existeDiagonalMenosLinha(e,l1,c1) == 1) && (l - 1) >= 0 && (c + 1) >= 0 && (l - 1) < 8 && (c + 1) < 8) {
            s[contador] = (l - 1);
            contador++;
            s[contador] = (c + 1);
            contador++;
            l--;
            c++;
        }
        l = l1;
        c = c1;
        while (e.grelha[l + 1][c - 1] == VALOR_O && (existeDiagonalMenosColuna(e,l1,c1) == 1) && (l + 1) >= 0 && (c - 1) >= 0 && (l + 1) < 8 && (c - 1) < 8) {
            s[contador] = (l + 1);
            contador++;
            s[contador] = (c - 1);
            contador++;
            l++;
            c--;
        }
        l = l1;
        c = c1;
        for (i = 0; i < contador; i = i + 2) {
            e.grelha[s[i]][s[i + 1]] = VALOR_X;
        }
    }
    if (e.peca == VALOR_O) {
        l1 = l;
        c1 = c;
        contador = 0;
        while (e.grelha[l - 1][c] == VALOR_X && (existeColunaCima(e,l1,c1) == 1) && (l - 1) >= 0 && c >= 0 && (l - 1) < 8 && c < 8) {
            s[contador] = (l - 1);
            contador++;
            s[contador] = c;
            contador++;
            l--;
        }
        l = l1;
        while (e.grelha[l + 1][c] == VALOR_X && (existeColunaBaixo(e,l1,c1) == 1) && (l + 1) >= 0 && c >= 0 && (l + 1) < 8 && c < 8) {
            s[contador] = (l + 1);
            contador++;
            s[contador] = c;
            contador++;
            l++;
        }
        l = l1;
        while (e.grelha[l][c - 1] == VALOR_X && (existeLinhaEsquerda(e,l1,c1) == 1) && l >= 0 && (c - 1) >= 0 && l < 8 && (c - 1) < 8) {
            s[contador] = l;
            contador++;
            s[contador] = (c - 1);
            contador++;
            c--;
        }
        c = c1;
        while (e.grelha[l][c + 1] == VALOR_X && (existeLinhaDireita(e,l1,c1) == 1) && l >= 0 && (c + 1) >= 0 && l < 8 && (c + 1) < 8) {
            s[contador] = l;
            contador++;
            s[contador] = (c + 1);
            contador++;
            c++;
        }
        c = c1;
        while (e.grelha[l - 1][c - 1] == VALOR_X && (existeDiagonalEsquerda(e,l1,c1) == 1) && (l - 1) >= 0 && (c - 1) >= 0 && (l - 1) < 8 && (c - 1) < 8) {
            s[contador] = (l - 1);
            contador++;
            s[contador] = (c - 1);
            contador++;
            l--;
            c--;
        }
        l = l1;
        c = c1;
        while (e.grelha[l + 1][c + 1] == VALOR_X && (existeDiagonalDireita(e,l1,c1) == 1) && (l + 1) >= 0 && (c + 1) >= 0 && (l + 1) < 8 && (c + 1) < 8) {
            s[contador] = (l + 1);
            contador++;
            s[contador] = (c + 1);
            contador++;
            l++;
            c++;
        }
        l = l1;
        c = c1;
        while (e.grelha[l - 1][c + 1] == VALOR_X && (existeDiagonalMenosLinha(e,l1,c1) == 1) && (l - 1) >= 0 && (c + 1) >= 0 && (l - 1) < 8 && (c + 1) < 8) {
            s[contador] = (l - 1);
            contador++;
            s[contador] = (c + 1);
            contador++;
            l--;
            c++;
        }
        l = l1;
        c = c1;
        while (e.grelha[l + 1][c - 1] == VALOR_X && (existeDiagonalMenosColuna(e,l1,c1) == 1) && (l + 1) >= 0 && (c - 1) >= 0 && (l + 1) < 8 && (c - 1) < 8) {
            s[contador] = (l + 1);
            contador++;
            s[contador] = (c - 1);
            contador++;
            l++;
            c--;
        }
        l = l1;
        c = c1;
        for (int i = 0; i < contador; i = i + 2) {
            e.grelha[s[i]][s[i + 1]] = VALOR_O;
        }
    }
    if (e.peca == VALOR_O) {
        e.grelha[l][c] = VALOR_O;
    }
    else {
        e.grelha[l][c] = VALOR_X;
    }
    return e;
}

/**
	Função que Verifica se uma Jogada Numa Determinada Linha e numa Determinada Coluna, é Válida.
*/

int jogadaValida (ESTADO e, int l, int c) {
    if (e.grelha[l][c] == VALOR_S) {
        return 0;
    }
    else {
        return 1;
    }
}

/**
	Função que Verifica se Desde a Peça Jogada até Qualquer Outra do Jogador, só Existem Peças do Adversário. 
	Em Caso Afirmativo, Converte Essas Peças.
	Para a Linha Esquerda.
*/

int existeLinhaEsquerda (ESTADO e, int l, int c) {
    if (e.peca == VALOR_X) {
        while (e.grelha[l][c - 1] == VALOR_O && (c - 1) >= 0) {
            c--;
        }
        if (e.grelha[l][c - 1] == VALOR_X && (c - 1) >= 0) {
            return 1;
        }
        else {
            return 0;
        }
    }
    else {
        while (e.grelha[l][c - 1] == VALOR_X && (c - 1) >= 0) {
            c--;
        }
        if (e.grelha[l][c - 1] == VALOR_O && (c - 1) >= 0) {
            return 1;
        }
        else {
            return 0;
        }
    }
}

/**
	Função que Verifica se Desde a Peça Jogada até Qualquer Outra do Jogador, só Existem Peças do Adversário. 
	Em Caso Afirmativo, Converte Essas Peças.
	Para a Linha Direita.
*/

int existeLinhaDireita (ESTADO e, int l, int c) {
    if (e.peca == VALOR_X) {
        while (e.grelha[l][c + 1] == VALOR_O && (c + 1) < 8) {
            c++;
        }
        if (e.grelha[l][c + 1] == VALOR_X && (c + 1) < 8) {
            return 1;
        }
        else {
            return 0;
        }
    }
    else {
        while (e.grelha[l][c + 1] == VALOR_X && (c + 1) < 8) {
            c++;
        }
        if (e.grelha[l][c + 1] == VALOR_O && (c + 1) < 8) {
            return 1;
        }
        else {
            return 0;
        }
    }
}

/**
	Função que Verifica se Desde a Peça Jogada até Qualquer Outra do Jogador, só Existem Peças do Adversário. 
	Em Caso Afirmativo, Converte Essas Peças.
	Para a Coluna de Cima.
*/

int existeColunaCima (ESTADO e, int l, int c) {
    if (e.peca == VALOR_X) {
        while (e.grelha[l - 1][c] == VALOR_O && (l - 1) >= 0) {
            l--;
        }
        if (e.grelha[l - 1][c] == VALOR_X && (l - 1) >= 0) {
            return 1;
        }
        else {
            return 0;
        }
    }
    else {
        while (e.grelha[l - 1][c] == VALOR_X && (l - 1) >= 0) {
            l--;
        }
        if (e.grelha[l - 1][c] == VALOR_O && (l - 1) >= 0) {
            return 1;
        }
        else {
            return 0;
        }
    }
}

/**
	Função que Verifica se Desde a Peça Jogada até Qualquer Outra do Jogador, só Existem Peças do Adversário. 
	Em Caso Afirmativo, Converte Essas Peças.
	Para a Coluna de Baixo.
*/

int existeColunaBaixo (ESTADO e, int l, int c) {
    if (e.peca == VALOR_X) {
        while (e.grelha[l + 1][c] == VALOR_O && (l + 1) < 8) {
            l++;
        }
        if (e.grelha[l + 1][c] == VALOR_X && (l + 1) < 8) {
            return 1;
        }
        else {
            return 0;
        }
    }
    else {
        while (e.grelha[l + 1][c] == VALOR_X && (l + 1) < 8) {
            l++;
        }
        if (e.grelha[l + 1][c] == VALOR_O && (l + 1) < 8) {
            return 1;
        }
        else {
            return 0;
        }
    }
}

/**
	Função que Verifica se Desde a Peça Jogada até Qualquer Outra do Jogador, só Existem Peças do Adversário. 
	Em Caso Afirmativo, Converte Essas Peças.
	Para a Diagonal Esquerda.
*/

int existeDiagonalEsquerda (ESTADO e, int l, int c) {
    if (e.peca == VALOR_X) {
        while (e.grelha[l - 1][c - 1] == VALOR_O && (l - 1) >= 0 && (c - 1) >= 0) {
            l--;
            c--;
        }
        if (e.grelha[l - 1][c - 1] == VALOR_X && (l - 1) >= 0 && (c - 1) >= 0) {
            return 1;
        }
        else {
            return 0;
        }
    }
    else {
        while (e.grelha[l - 1][c - 1] == VALOR_X && (l - 1) >= 0 && (c - 1) >= 0) {
            l--;
            c--;
        }
        if (e.grelha[l - 1][c - 1] == VALOR_O && (l - 1) >= 0 && (c - 1) >= 0) {
            return 1;
        }
        else {
            return 0;
        }
    }
}

/**
	Função que Verifica se Desde a Peça Jogada até Qualquer Outra do Jogador, só Existem Peças do Adversário. 
	Em Caso Afirmativo, Converte Essas Peças.
	Para a Diagonal Direita.
*/

int existeDiagonalDireita (ESTADO e, int l, int c) {
    if (e.peca == VALOR_X) {
        while (e.grelha[l + 1][c + 1] == VALOR_O && (l + 1) < 8 && (c + 1) < 8) {
            l++;
            c++;
        }
        if (e.grelha[l + 1][c + 1] == VALOR_X && (l + 1) < 8 && (c + 1) < 8) {
            return 1;
        }
        else {
            return 0;
        }
    }
    else {
        while (e.grelha[l + 1][c + 1] == VALOR_X && (l + 1) < 8 && (c + 1) < 8) {
            l++;
            c++;
        }
        if (e.grelha[l + 1][c + 1] == VALOR_O && (l + 1) < 8 && (c + 1) < 8) {
            return 1;
        }
        else {
            return 0;
        }
    }
}

/**
	Função que Verifica se Desde a Peça Jogada até Qualquer Outra do Jogador, só Existem Peças do Adversário. 
	Em Caso Afirmativo, Converte Essas Peças.
	Para o Canto Superior Direito.
*/

int existeDiagonalMenosLinha (ESTADO e, int l, int c) {
    if (e.peca == VALOR_X) {
        while (e.grelha[l - 1][c + 1] == VALOR_O && (l - 1) >= 0 && (c + 1) < 8) {
            l--;
            c++;
        }
        if (e.grelha[l - 1][c + 1] == VALOR_X && (l - 1) >= 0 && (c + 1) < 8) {
            return 1;
        }
        else {
            return 0;
        }
    }
    else {
        while (e.grelha[l - 1][c + 1] == VALOR_X && (l - 1) >= 0 && (c + 1) < 8) {
            l--;
            c++;
        }
        if (e.grelha[l - 1][c + 1] == VALOR_O && (l - 1) >= 0 && (c + 1) < 8) {
            return 1;
        }
        else {
            return 0;
        }
    }
}

/**
	Função que Verifica se Desde a Peça Jogada até Qualquer Outra do Jogador, só Existem Peças do Adversário. 
	Em Caso Afirmativo, Converte Essas Peças.
	Para o Canto Inferior Esquerdo.
*/

int existeDiagonalMenosColuna (ESTADO e, int l, int c) {
    if (e.peca == VALOR_X) {
        while (e.grelha[l + 1][c - 1] == VALOR_O && (l + 1) < 8 && (c - 1) >= 0) {
            l++;
            c--;
        }
        if (e.grelha[l + 1][c - 1] == VALOR_X && (l + 1) < 8 && (c - 1) >= 0) {
            return 1;
        }
        else {
            return 0;
        }
    }
    else {
        while (e.grelha[l + 1][c - 1] == VALOR_X && (l + 1) < 8 && (c - 1) >= 0) {
            l++;
            c--;
        }
        if (e.grelha[l + 1][c - 1] == VALOR_O && (l + 1) < 8 && (c - 1) >= 0) {
            return 1;
        }
        else {
            return 0;
        }
    }
}

/**
	Função que Verifica se o Comando Inserido Pelo Utilizador Possuí o Formato Correto.
	Exemplo: L <Ficheiro>, J L C. Basicamente, verifica que Existe o Espaço Entre o Primeiro Caracter.
	Além Disso, Impede que o Utilizador Insira Qualquer Tipo de Caracter à Frente do Comando.
*/

int verificaSpaces (char comando [200], int x) {
    int contador = 0;
    int i = 0;
    i = x;
    while (comando[i] && contador == 0) {
        if (isspace(comando[i])) {
            i++;
        } else if (comando[i] == '\n') {
            contador = 1;
        }
        else {
            contador = 2;
        }
    }
    if (contador == 0 || contador == 1) {
        return 0;
    }
    else {
        return 1;
    }
}