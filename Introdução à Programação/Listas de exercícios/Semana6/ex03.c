#include <stdio.h>
#include <locale.h>


/* 3. Fa�a um programa que preencha uma matriz de tamanho N � N (o tamanho deve ser
informado pelo usu�rio) e imprima o maior elemento de cada coluna da matriz. */
int main() {
	setlocale(LC_ALL, "Portuguese");
	
	int n, i, j;
	printf("Determine o tamanho da matriz N x N: ");
	scanf("%d", &n);
	int matrix[n][n], colhigher[n];
	
	if (n <= 0) {
		printf("Tamanho inv�lido!");
		return 0;
	}
	printf("Preencha a matriz %d x %d com valores inteiros:\n", n, n);
	
	/* L� a primeira linha. */
	i = 0;
	
	for (j = 0; j < n; ++j) {
		printf("[%d, %d] = ", i, j);
		scanf("%d", &matrix[i][j]);
		colhigher[j] = matrix[i][j];
	}
	
	for (i = 1; i < n; ++i) { // L� as linhas restantes.
		
		for (j = 0; j < n; ++j) {
			printf("[%d, %d] = ", i, j);
			scanf("%d", &matrix[i][j]);
			
			if (matrix[i][j] > colhigher[j])
				colhigher[j] = matrix[i][j];
		}
	}
	
	printf("Os maiores elementos de cada coluna s�o:");
	
	for (j = 0; j < n; ++j) {
		printf(" [%d]", colhigher[j]);
	}
	
	return 0;
}

