#include <stdio.h>
#include <locale.h>

#define LINES 5
#define COLUMNS 3


int main() {
    setlocale(LC_ALL, "Portuguese");

    int i, j;
    int matrix[LINES][COLUMNS], medium[LINES];

    printf("Preencha uma matriz %d x %d com números inteiros:\n", LINES, COLUMNS);

    for (i = 0; i < LINES; ++i) {
        for (j = 0; j < COLUMNS; ++j) {
            printf("a%d%d: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
        medium[i] = 0;
    }

    for (i = 0; i < LINES; ++i) {
        printf("|");

        for (j = 0; j < COLUMNS; ++j) {
            printf(" %2d", matrix[i][j]);
            medium[i] += matrix[i][j];
        }
        printf(" |\n");
        medium[i] /= COLUMNS;
    }

    printf("\nA média de cada linha é: \n");
    
    for (i = 0; i < LINES; ++i) 
        printf("%d° = %d\n", i + 1, medium[i]);

    return 0;
}
