#include <stdio.h>
#include <locale.h>


/* 2. Faça um programa que leia uma matriz 4 × 4 de números inteiros do usuário e:
(a) Imprima a soma dos elementos que estão em colunas ímpares.
(b) Imprima a média dos elementos que estão em linhas pares.
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
	printf("A soma dos elementos das colunas ímpares é: %d\n", oddcols_sum);
	printf("A média dos elementos nas linhas pares é: %.2f", (float) evenlines_sum / (2.0 * 4.0)); // A média é "Sum / (Even Lines * Columns)"
	
	return 0;
}

