#include <stdio.h>
#include <locale.h>


int main() {
    setlocale(LC_ALL, "Portuguese");

    int i, j, diagonalsum = 0;
    int matrix[3][3];

    printf("Preencha uma matriz 3x3 com n�meros inteiros:\n");

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            printf("a%d%d: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }

    printf("\nMatriz:\n");

    for (i = 0; i < 3; ++i) {
        printf("|");

        for (j = 0; j < 3; ++j) {
            printf(" %2d", matrix[i][j]);
        }
        printf(" |\n");
    }
    
    printf("\nMatriz Diagonal:\n");

    for (i = 0; i < 3; ++i) {
        printf("|");

        for (j = 0; j < 3; ++j) {

            if (i == j){ // Matriz diagonal. Para a diagonal secund�ria inclua: `|| i + j == 4` sendo 4 a constante "k" da diagonal secund�ria
                printf(" %2d", matrix[i][j]);
                diagonalsum += matrix[i][j];
            }
            else
                printf("   ");
        }
        printf(" |\n");
    }
    //for (i = 0; i < 3; ++i) matrix[i][j]; // Note que � poss�vel obter a diagonal principal com um �nico loop.

    printf("\nA soma dos elementos da diagonal principal � %d.\n", diagonalsum);

    return 0;
}
