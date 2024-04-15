#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// Definindo constantes
int linhas = 15;
int colunas = 15;

// Estrutura para a posição da cobrinha
typedef struct {
    int x;
    int y;
} Posicao; //Criando variável do tipo Posição que é uma struct com as coordenadas da cobrinha

//Declarando funções
void gerar_arena();
void gerar_maca();
void imprimirTudo();
int func_movimento(char direcao);
void print_game_over();
//Estruturando cobrinha em forma de lista ordenada -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

const unsigned MAX = 169; //Tamanho da arena tirando as bordas
char l[169]; //Para a cobrinha em lista um array de chars será usado
int pos = 0; //Posição inicial

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
Posicao cobrinha[169]; //Criando variável chamada "cobrinha" do tipo Posição
char movimento; //Instrução para movimento da cobrinha
char resposta[10];

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

int linha_maca_global = 0;
int coluna_maca_global = 0;

void gerar_maca() {

    // Gera um índice aleatório para a linha e a coluna
    srand(time(NULL));//timenull -> Numero para a seed para a geração pseudo-aleatória

    //Ja que a area de fato do jogo é 13x13:

    int linha_aleatoria, coluna_aleatoria;

    //Faça enquanto, aprendi para corrigir o bug em que a maçã surge na cobrinha e desaparece do jogo depois
    do {
        linha_aleatoria = rand() % (linhas - 2) + 1; // Evita as bordas superior e inferior
        coluna_aleatoria = rand() % (colunas - 2) + 1; // Evita as bordas esquerda e direita
    } while (arena[linha_aleatoria][coluna_aleatoria] != ' '); // Enquanto a posição nao for um espaço em branco continue gerando

    //linha_aleatoria = 7; //teste
    //coluna_aleatoria = 7; //teste

    if (linha_aleatoria == 7 && coluna_aleatoria == 7) { linha_aleatoria--; } //Caso a maçã apareça na posição inicial no início do jogo

    // Coloca um símbolo aleatório na posição aleatória
    char maca = '@';
    arena[linha_aleatoria][coluna_aleatoria] = maca;

    linha_maca_global = linha_aleatoria;
    coluna_maca_global = coluna_aleatoria;
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

int func_movimento(char direcao) {
     
    arena[0][0] = '#'; //Hotfix: bug do terminal em que o # superior esquerdo some

    // Lê o movimento do jogador
    if (direcao == 'W' || direcao == 'w') { //Indo para cima
        arena[cobrinha[0].x][cobrinha[0].y] = ' ';
        cobrinha[0].x--; //linha -1 coluna não mexe

        if (cobrinha[0].x == 0 || cobrinha[0].x == 14) {
            return 0;
        }

        arena[cobrinha[0].x][cobrinha[0].y] = 'O'; //Atualiza cobrinha na matriz
        return 1; //retorna 1 para indicar que o movimento foi realizado
    }
    else if (direcao == 'A' || direcao == 'a') { //Indo para esquerda
        arena[cobrinha[0].x][cobrinha[0].y] = ' ';
        cobrinha[0].y--; //coluna -1 linha não mexe

        if (cobrinha[0].y == 0 || cobrinha[0].y == 14) {
            return 0;
        }

        arena[cobrinha[0].x][cobrinha[0].y] = 'O'; //Atualiza cobrinha na matriz
        return 1; //retorna 1 para indicar que o movimento foi realizado
    }
    else if (direcao == 'S' || direcao == 's') { //Indo para baixo
        arena[cobrinha[0].x][cobrinha[0].y] = ' ';
        cobrinha[0].x++; //linha -1 coluna não mexe

        if (cobrinha[0].x == 0 || cobrinha[0].x == 14) {
            return 0;
        }

        arena[cobrinha[0].x][cobrinha[0].y] = 'O'; //Atualiza cobrinha na matriz
        return 1; //retorna 1 para indicar que o movimento foi realizado
    }
    else if (direcao == 'D' || direcao == 'd') { //Indo para direita
        arena[cobrinha[0].x][cobrinha[0].y] = ' ';
        cobrinha[0].y++; //coluna +1 linha não mexe

        if (cobrinha[0].y == 0 || cobrinha[0].y == 14) {
            return 0;
        }

        arena[cobrinha[0].x][cobrinha[0].y] = 'O'; //Atualiza cobrinha na matriz
        return 1; //retorna 1 para indicar que o movimento foi realizado
    }
    else { return -1; } //retorna 0 para indicar que o movimento NÃO foi realizado
}

void print_game_over() { //Mensagem personalizada de game over 
    char game_over[] =
        "\n"
        "\n"
        " $$$$$$\\                                           $$$$$$\\                                 $$\\ \n"
        "$$  __$$\\                                         $$  __$$\\                                $$ |\n"
        "$$ /  \\__| $$$$$$\\  $$$$$$\\$$$$\\   $$$$$$\\        $$ /  $$ |$$\\    $$\\  $$$$$$\\   $$$$$$\\  $$ |\n"
        "$$ |$$$$\\  \\____$$\\ $$  _$$  _$$\\ $$  __$$\\       $$ |  $$ |\\$$\\  $$  |$$  __$$\\ $$  __$$\\ $$ |\n"
        "$$ |\\_$$ | $$$$$$$ |$$ / $$ / $$ |$$$$$$$$ |      $$ |  $$ | \\$$\\$$  / $$$$$$$$ |$$ |  \\__|\\__|\n"
        "$$ |  $$ |$$  __$$ |$$ | $$ | $$ |$$   ____|      $$ |  $$ |  \\$$$  /  $$   ____|$$ |          \n"
        "\\$$$$$$  |\\$$$$$$$ |$$ | $$ | $$ |\\$$$$$$$\\        $$$$$$  |   \\$  /   \\$$$$$$$\\ $$ |      $$\\ \n"
        " \\______/  \\_______|\\__| \\__| \\__| \\_______|       \\______/     \\_/     \\_______|\\__|      \\__|\n"
        "                                                                                                \n"
        "                                                                                                \n"
        "                                                                                                \n";

    printf("%s", game_over);
}



int main(void) {

    //Terminal em 1250 x 650 pixels de resolução para a melhor visualização

    printf("  /$$$$$$  /$$$$$$$  /$$$$$$$$       /$$     /$$ /$$$$$$  /$$   /$$       /$$$$$$$  /$$$$$$$$  /$$$$$$  /$$$$$$$  /$$     /$$ /$$$$ \n");
    Sleep(500); // Atraso de 0.5 segundo (500.000 microssegundos)
    printf(" /$$__  $$| $$__  $$| $$_____/      |  $$   /$$//$$__  $$| $$  | $$      | $$__  $$| $$_____/ /$$__  $$| $$__  $$|  $$   /$$//$$  $$\n");
    Sleep(500); // Atraso de 0.5 segundo
    printf("| $$  \\ $$| $$  \\ $$| $$             \\  $$ /$$/| $$  \\ $$| $$  | $$      | $$  \\ $$| $$      | $$  \\ $$| $$  \\ $$ \\  $$ /$$/|__\\ $$\n");
    Sleep(500); // Atraso de 0.5 segundo
    printf("| $$$$$$$$| $$$$$$$/| $$$$$           \\  $$$$/ | $$  | $$| $$  | $$      | $$$$$$$/| $$$$$   | $$$$$$$$| $$  | $$  \\  $$$$/     /$$/\n");
    Sleep(500); // Atraso de 0.5 segundo
    printf("| $$__  $$| $$__  $$| $$__/            \\  $$/  | $$  | $$| $$  | $$      | $$__  $$| $$__/   | $$__  $$| $$  | $$   \\  $$/     /$$/ \n");
    Sleep(500); // Atraso de 0.5 segundo
    printf("| $$  | $$| $$  \\ $$| $$                | $$   | $$  | $$| $$  | $$      | $$  \\ $$| $$      | $$  | $$| $$  | $$    | $$     |__/  \n");
    Sleep(500); // Atraso de 0.5 segundo
    printf("| $$  | $$| $$  | $$| $$$$$$$$          | $$   |  $$$$$$/|  $$$$$$/      | $$  | $$| $$$$$$$$| $$  | $$| $$$$$$$/    | $$      /$$  \n");
    Sleep(500); // Atraso de 0.5 segundo
    printf("|__/  |__/|__/  |__/|________/          |__/    \\______/  \\______/       |__/  |__/|________/|__/  |__/|_______/     |__/     |__/   \n");
    Sleep(500); // Atraso de 0.5 segundo

    printf("\n");
    printf("\n");

    printf("                                         DIGITE \"START\" PARA COMEÇAR: ");
    scanf_s(" %9s", resposta, 10);


    //char resposta[] = "start"; //Acesso direto do jogo para facilitar desenvolvimento e testes
    if (strcmp(resposta, "START") == 0 || strcmp(resposta, "start") == 0 || strcmp(resposta, "Start") == 0) {

        int tamanho_cobrinha = 1; //Tamanho 1 pois so tem a cabeça
        system("cls"); //Limpa terminal

        gerar_arena(); //Gerar arena da cobrinha
        adicionar_cobrinha(); //Gerar cobrinha no meio da arena
        gerar_maca();//Gerar maçã em uma posição aleatória da arena
        imprimirTudo(); //Gerar tudo no terminal

        printf("\n");
        printf("Digite para onde você quer ir com W-A-S-D: ");
        scanf_s(" %c", &movimento); // Adicionado espaço antes do %c para consumir o caractere de nova linha

        while (movimento != 'Q' && movimento != 'q') {

            if (cobrinha[0].x == linha_maca_global && cobrinha[0].y == coluna_maca_global) {
                // Incrementar o tamanho da cobrinha
                inserir('o'); //aumenta cobrinha na lista
                tamanho_cobrinha++;
                // Gerar nova posição para a maçã
                gerar_maca();
                // Atualizar a visualização da cobrinha e da maçã na matriz da arena
                imprimirTudo();
            }

            // Atualize as posições do corpo para seguir a cabeça
            if (tamanho_cobrinha > 1) {
                for (int i = tamanho_cobrinha - 1; i > 0; i--) {
                    cobrinha[i] = cobrinha[i - 1];
                }
            }

            int movimento_valido = func_movimento(movimento);
            int oldx = 0;
            int oldy = 0;

            if (movimento_valido == 1) {

                system("cls"); //Limpa terminal

                for (int i = 1; i < tamanho_cobrinha; i++) {
                    arena[cobrinha[i].x][cobrinha[i].y] = 'o'; // Use 'o' (letra minúscula) para representar o corpo da cobrinha

                    oldx = cobrinha[i].x; // Armazena a ultima posição x anterior
                    oldy = cobrinha[i].y; // Armazena a ultima posição y anterior
                }

                imprimirTudo(); //Gerar tudo no terminal
                arena[oldx][oldy] = ' '; // E limpo a ultima posição já que ela não tem mais sentido, nao faz mais parte da cobrinha, é antiga
            }

            else if (movimento_valido == 0) {
                system("cls"); //Limpa terminal
                print_game_over();
                break;
            }

            else {
                printf("Comando inválido, nenhum movimento foi realizado\n");
            }

            printf("\n");


            int ajuda = 0;//Para quebrar o while de fora
            for (int i = 1; i < tamanho_cobrinha; i++) { //Vendo todas as posições da cobrinha
                if (cobrinha[0].x == cobrinha[i].x && cobrinha[0].y == cobrinha[i].y) { //Checado se a cabeça da cobrinha colidiu com o corpo
                    system("cls"); //Limpa terminal
                    print_game_over();
                    ajuda = 1;//Para quebrar o while de fora
                    break;
                }
            }

            if (ajuda == 1) { //Para quebrar o while de fora
                break; //Quebra o while de fora
            }

            printf("Digite para onde você quer ir com W-A-S-D: ");
            scanf_s(" %c", &movimento); // Adicionado espaço antes do %c para consumir o caractere de nova linha

        } //chave do while
    } //chave do if

    return 0;
} //chave do main