#ifndef UNTITLED1_ESTADO_H
#define UNTITLED1_ESTADO_H
#define BUFFERSIZE 200

///
/// @brief Estrutura que Armazena os Tipos de Valores do Jogo.
///
/// 5 Valores, X, O, S, H, Vazia.
///

typedef enum {VAZIA, VALOR_X, VALOR_O, VALOR_S, VALOR_H} VALOR;

///
/// @brief Estrutura que Armazena o Estado de Jogo.
///
///	O Estado é Constuído por a Peça a Jogar, O Tabuleiro de Jogo e o Modo de Jogo.
///

typedef struct estado {
    VALOR peca;
    VALOR grelha [8][8];
    char modo;
} ESTADO;

///
/// @brief Estrutura que Armazena uma Lista Ligada para a Execução do Comando UNDO.
///
///	A Lista Ligada é Constuída Pelo Estado de Jogo Atual e por um Apontador Para a Próxima Lista.
///

typedef struct listaL {
    ESTADO estado;
    struct listaL *next;
} *LL;

///
/// Funções de Preparação e Execução do Estado Inicial do Jogo.
///

ESTADO mapaInicial (ESTADO e);

///
/// Funções de Save e Load do Estado de Jogo a Partir de um Ficheiro de Texto.
///

ESTADO loads (ESTADO e, char text[100]);
void saves (ESTADO e, char text[100]);
int extraiModo (char text[100]);

///
/// Função que Imprime o Menu de Escolha da Operação.
///

void menu ();

///
/// Função que Imprime o Estado Atual do Jogo.
///

void printa (ESTADO e);
void escondePontos (ESTADO e);

///
/// Função Auxiliar que Calcula o Score de Cada Jogador.
///

int score (ESTADO e, char p);
void imprimeArrayValidas (ESTADO e);

///
/// Funções de Controlo de Situações de Skip e Fim de Jogo.
///

ESTADO situacaoDeSkip (ESTADO e);
int fimDeJogo (ESTADO e);
char contaScore (ESTADO e);

///
/// Funções Auxiliares para a Atualização do Jogo.
///

ESTADO limpaPontos (ESTADO e);
ESTADO trocaJogador (ESTADO e);
int contaJogadasValidas (ESTADO e);
ESTADO sugestaoAleatoria (ESTADO e);
ESTADO apagaSugestao (ESTADO e);

///
/// Funções do UNDO.
///

LL pushEstado (LL llig, ESTADO e);
LL popEstado (LL llig);

///
/// Função Para Libertar Todo o Espaço Ocupado Pela Lista Ligada.
///

void freeL (LL llig);

///
/// Funções Auxiliares Para a Realização de uma Jogada.
///

ESTADO verificaLinha (ESTADO e);
ESTADO verificaColuna (ESTADO e);
ESTADO verificaDiagonal (ESTADO e);
ESTADO converte (ESTADO e, int l, int c);
int jogadaValida (ESTADO e, int l, int c);
int existeLinhaEsquerda (ESTADO e, int l, int c);
int existeLinhaDireita (ESTADO e, int l, int c);
int existeColunaCima (ESTADO e, int l, int c);
int existeColunaBaixo (ESTADO e, int l, int c);
int existeDiagonalEsquerda (ESTADO e, int l, int c);
int existeDiagonalDireita (ESTADO e, int l, int c);
int existeDiagonalMenosLinha (ESTADO e, int l, int c);
int existeDiagonalMenosColuna (ESTADO e, int l, int c);

///
/// Função de Controlo de Strings.
///

int verificaSpaces (char comando [200], int x);


///
/// @brief Funções do Bot.
///

///
/// Imprime o Estado de Jogo.
///

void printaBot (ESTADO e, int x);

///
/// Executa uma Jogada de Bot Nível 1.
///

ESTADO sugestaoAleatoriaBOT (ESTADO e);
ESTADO jogadaBotEasy (ESTADO e, int x);
void escondePontosBOT (ESTADO e, int x);

///
/// Funções Auxiliares e de Execução de uma Jogada do Bot Nível 2.
///

ESTADO jogadaBotMedium (ESTADO e, int x);
int valorTabuleiro (int l, int c);

///
/// Funções Auxiliares e de Execução de uma Jogada do Bot Nível 3.
///

int maiorIndiceArray (int value[100], int x);
int maiorElementoArray (int value[100], int x);
ESTADO jogadaBotHard (ESTADO e, int x);
int removeElement (int value[100], int n, int p);

///
/// Funções de Save e Load do Bot.
///

void savesBOT (ESTADO e, char text[100], int x);
ESTADO loadsBOT (ESTADO e, char text []);
int extraiNivel (char text[100]);

///
/// Funções de UNDO do Bot.
///

LL popEstadoBOT (LL llig);
LL popEstadoBOTJogador (LL llig);

///
/// Função de Controlo de Situação de Skip do Bot.
///

int situacaoDeSkipBOT (ESTADO e);

#endif //UNTITLED1_ESTADO_H
