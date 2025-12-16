#include <stdio.h>
#include <stdlib.h>


// Função para salvar o progresso
void salvarArquivo(int matriz2[4][4], int matriz[4][4]) {
	int i, j;
    FILE *arquivo = fopen("sudoku.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao escrever arquivo\n");
        return;
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            fprintf(arquivo, "%d %d ", matriz[i][j], matriz2[i][j]);
        }
    }

    fclose(arquivo);
}

// Função para carregar o progresso
void carregarArquivo(int matriz2[4][4], int matriz[4][4]) {
	int i, j;
    FILE *arquivo = fopen("sudoku.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao ler arquivo\n");
        return;
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (fscanf(arquivo, "%d %d", &matriz[i][j], &matriz2[i][j]) != 2) {
                printf("Erro ao ler dados do arquivo\n");
                fclose(arquivo);
                return;
            }
        }
    }

    fclose(arquivo);
}

// Função principal do jogo
void jogar(int matriz[4][4], int matriz2[4][4]) {
	int i, j;
    int vidas = 3;
    int l, m, v;
    int num = 0;

    do {
        printf("     0   1   2   3\n");
        for (i = 0; i < 4; i++) {
            printf(" %d ", i);
            for (j = 0; j < 4; j++) {
                printf("|");
                if (matriz2[i][j] == 0) {
                    printf(" %d ", matriz[i][j]);
                } else {
                    printf(" ~ ");
                }
            }
            printf("\n");
        }

        printf("linha (0 - 3): ");
        scanf("%d", &l);
        printf("coluna (0 - 3): ");
        scanf("%d", &m);
        printf("valor (1 - 4): ");
        scanf("%d", &v);

        if (l < 0 || l > 3 || m < 0 || m > 3 || v < 1 || v > 4) {
            printf("Entrada invalida\n");
            continue;
        }

        if (v == matriz[l][m]) {
            printf("Parabens, voce acertou!\n");
            matriz2[l][m] = 0;
            salvarArquivo(matriz2, matriz);
        } else {
            printf("Voce errou!\n");
            vidas--;
            printf("Voce ainda tem %d vidas\n", vidas);
        }

        num = 0;
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (matriz2[i][j] == 1) {
                    num++;
                }
            }
        }

        if (num == 0) {
            printf("Parabens, voce ganhou!\n");
            break;
        }

        printf("Ainda faltam %d casas\n", num);

    } while (vidas > 0);

    if (vidas <= 0) {
        printf("Voce perdeu! Fim de jogo.\n");
    }
}


int main() {
	int i, j;
    int opcao;

    int tempMatriz[4][4] = {
        {4, 2, 1, 3},
        {1, 3, 2, 4},
        {3, 1, 4, 2},
        {2, 4, 3, 1}
    };

    int tempMatriz2[4][4] = {
        {0, 0, 1, 0},
        {1, 0, 0, 1},
        {1, 1, 1, 0},
        {0, 0, 1, 1}
    };

    int matriz[4][4];
    int matriz2[4][4];

    do {
        printf("\n1 - Novo Jogo\n");
        printf("2 - Carregar Jogo\n");
        printf("3 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                // Copia as matrizes iniciais para as matrizes de jogo
                for (i = 0; i < 4; i++) {
                    for (j = 0; j < 4; j++) {
                        matriz[i][j] = tempMatriz[i][j];
                        matriz2[i][j] = tempMatriz2[i][j];
                    }
                }
                jogar(matriz, matriz2);
                break;

            case 2:
                carregarArquivo(matriz2, matriz);
                jogar(matriz, matriz2);
                break;

            case 3:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opçao invalida!\n");
                break;
        }
    } while (opcao!=3);
}