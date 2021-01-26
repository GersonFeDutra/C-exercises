#include <stdio.h>
#include <locale.h>


int main() {
	setlocale(LC_ALL, "Portuguese");

	// Matrizes podem ser criadas por meio de ponteiros de ponteiros
	// Note que, como o método malloc é usado, essas matrizes são armazenadas na heap
	int **matrix = (int**)malloc(3 * sizeof(int*)); // 3 linhas
	
	for (int i = 0; i < 3; i++) {
		matrix[i] = (int*)malloc(3 * sizeof(int)); // 3 colunas
	}
	
	// Preenche a matriz
	int  i, j, cont = 1;
	for (i = 0; i < 3; ++i) {
		for (j = 0; j < 3; ++j) {
			matrix[i][j] = cont;
			cont++;
		}
	}
	
	// Imprime a matriz
	for (i = 0; i < 3; ++i) {
		for (j = 0; j < 3; ++j) {
			printf("%d ", *(*(matrix + i) + j));
			//printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}

	return 0;
}
