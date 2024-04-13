#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Definindo constantes
int linhas = 15;
int colunas = 15;

// Estrutura para a posição da cobrinha
typedef struct {
    int x;
    int y;
} Posição; //Criando variável do tipo Posição que é uma struct com as coordenadas da cobrinha

//Declarando funções
void gerar_arena();
void gerar_maçã();
void imprimirTudo();

//Estruturando cobrinha em forma de lista ordenada -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

const unsigned MAX = 169; //Tamanho da arena tirando as bordas
char l[169]; //Para a cobrinha em lista um array de chars será usado
pos = 0; //Posição inicial

//Declarando funções
void inserir(char elemento);
char obter(int indice);
int tamanho();
void imprimir();

//Criando Funções da cobrinha
void inserir(char elemento) {
    if (pos < MAX)
        l[pos++] = elemento;
    else {
        printf("Não foi possível inserir %c. Lista cheia.\n", elemento);
    }
}
char obter(int indice) {
    if (indice < 0 || indice >= pos) {
        printf("Indice %d fora dos limites da Lista.\n", indice);
        exit(1);
    }
    return l[indice];
}
int tamanho() {
    return pos;
}
void imprimir() {
    for (int i = 0; i < pos; i++)
        printf("%c ", l[i]);
    printf("\n");
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// Variáveis globais
char arena[15][15]; //Layout do jogo
Posição cobrinha[169]; //Criando variável chamada "cobrinha" do tipo Posição

void gerar_arena() {
    int i, j;

    for (i = 0; i < linhas; i++) {
        for (j = 0; j < colunas; j++) {
            if ((i == 0 || i == linhas - 1) && (j == 0 || j == colunas - 1)) {
                arena[i][j] = '#'; // Adiciona '#' nas quatro pontas
            }
            else if (i == 0 || i == linhas - 1) {
                arena[i][j] = '-'; // Adiciona hífens nas bordas superior e inferior
            }
            else if (j == 0 || j == colunas - 1) {
                arena[i][j] = '|'; // Adiciona barras verticais nas bordas esquerda e direita
            }
            else {
                arena[i][j] = ' '; // Espaço em branco no interior da matriz
            }
        }
    }
}

void gerar_maçã() {

    // Gera um índice aleatório para a linha e a coluna
    srand(time(NULL));//timenull -> Numero para a seed para a geração pseudo-aleatória

    //Ja que a area de fato do jogo é 13x13:

    int linha_aleatoria = rand() % (linhas - 2) + 1;
    // Evita as bordas superior e inferior

    int coluna_aleatoria = rand() % (colunas - 2) + 1;
    // Evita as bordas esquerda e direita

//linha_aleatoria = 7; //teste
//coluna_aleatoria = 7; //teste

    if (linha_aleatoria == 7 && coluna_aleatoria == 7) { linha_aleatoria--; }
    // Coloca um símbolo aleatório na posição aleatória
    char maçã = '@';
    arena[linha_aleatoria][coluna_aleatoria] = maçã;

}

// Função para adicionar a cobrinha à matriz
void adicionar_cobrinha() {
    cobrinha[0].x = 7; // Posição inicial da cobrinha no meio da arena
    cobrinha[0].y = 7; // Posição inicial da cobrinha no meio da arena
    arena[cobrinha[0].x][cobrinha[0].y] = 'O'; // Símbolo da cobrinha na posição inicial
}

// Função para imprimir a arena
void imprimirTudo() {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%1c ", arena[i][j]); // Espaçamento entre os caracteres
        }
        printf("\n");
    }
}

int main(void) {
    gerar_arena(); //Gerar arena da cobrinha
    adicionar_cobrinha(); //Gerar cobrinha no meio da arena
    gerar_maçã();//Gerar maçã em uma posição aleatória da arena
    imprimirTudo(); //Gerar tudo no terminal
    return 0;
}