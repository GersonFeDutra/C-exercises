#include <stdio.h>
#include <locale.h>


/* 2. Fa�a um programa que leia uma matriz 4 � 4 de n�meros inteiros do usu�rio e:
(a) Imprima a soma dos elementos que est�o em colunas �mpares.
(b) Imprima a m�dia dos elementos que est�o em linhas pares.
*/
int main() {
	setlocale(LC_ALL, "Portuguese");
	
	int i, j, evenlines_sum, oddcols_sum;
	int matrix[4][4];
	oddcols_sum = evenlines_sum = 0;
	
	printf("Preencha uma matriz 4 x 4 com valores inteiros:\n");
		
	for (i = 0; i < 4; ++i) {
		
		for (j = 0; j < 4; ++j) {
			printf("[%d, %d] = ", i, j);
			scanf("%d", &matrix[i][j]);
			
			if (i % 2 == 0)
				evenlines_sum += matrix[i][j];
			
			if (j % 2 == 1)
				oddcols_sum += matrix[i][j];
		}
	}
	printf("A soma dos elementos das colunas �mpares �: %d\n", oddcols_sum);
	printf("A m�dia dos elementos nas linhas pares �: %.2f", (float) evenlines_sum / (2.0 * 4.0)); // A m�dia � "Sum / (Even Lines * Columns)"
	
	return 0;
}

