#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Definindo constantes
int linhas = 15;
int colunas = 15;

//Declarando funções
void gerar_arena();
void gerar_maçã();
void imprimir();

// Variáveis globais
char arena[15][15]; //Layout do jogo

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

void gerar_maçã(){

    // Gera um índice aleatório para a linha e a coluna
    srand(time(NULL));//timenull -> Numero para a seed para a geração pseudo-aleatória

    //Ja que a area de fato do jogo é 13x13:

    int linha_aleatoria = rand() % (linhas - 2) + 1; 
                                   // Evita as bordas superior e inferior

    int coluna_aleatoria = rand() % (colunas - 2) + 1; 
                                    // Evita as bordas esquerda e direita

    // Coloca um símbolo aleatório na posição aleatória
    char maçã = '@';
    arena[linha_aleatoria][coluna_aleatoria] = maçã;

}


// Função para imprimir a arena
void imprimir() {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%4c ", arena[i][j]); // Espaçamento entre os caracteres
        }
        printf("\n");
    }
}

int main(void) {
    gerar_arena(); //Gerar arena da cobrinha
    gerar_maçã();//Gerar maçã em uma posição aleatória da arena
    imprimir(); //Gerar tudo no terminal
    return 0;
}