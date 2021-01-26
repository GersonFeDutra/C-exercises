#include <stdio.h>
#include <locale.h>

#define FALSE 0
#define TRUE 1

/* 2. Faça um algoritmo que leia dois números do usuário: m e n. Peça para o usuário preencher
uma matriz de inteiros de tamanho m × n. Além disso, o usuário deve preencher um
vetor de inteiros de tamanho n. Dado esse contexto:
(a) Crie um algoritmo que imprima "A matriz possui uma linha igual ao vetor"caso
exista uma linha na matriz igual ao vetor. Caso contrário, o algoritmo deve imprimir
"A matriz NÃO possui uma linha que seja igual ao vetor". (2.0)
(b) Crie um algoritmo que identique e imprima o menor elemento da matriz. Além
disso, ele deve imprimir a linha e a coluna em que esse elemento se encontra. (2.0) */
struct coord_value {
	int value;
	int x;
	int y;
};
 
int main() {
	void lecker_check(int* array, int size);
	setlocale(LC_ALL, "Portuguese");
	
	int m, n, i, j;
	printf("Insira dois números:\nm = ");
	scanf("%d", &m);
	
	printf("n = ");
	scanf("%d", &n);
	
	printf("Preencha uma matriz %d x %d:\n", m, n);
	//int matrix[i][j] = (**int)malloc(sizeof(int) * n)mallocc(sizeof(int) *m);
	int matrix[m][n];
	
	for (i = 0; i < m; i++) {
		
		for (j = 0; j < n; j++) {
			printf("[%d, %d] = ", i, j);
			scanf("%d", &matrix[i][j]);
		}
	}
	
	int array[n];
	printf("Preencha um vetor de tamanho %d:\n", n);
	
	for (i = 0; i < n; i++) {
		printf("[%d] = ", i);
		scanf("%d", &array[i]);
	}
	
	
	// a
	int counter = 0;
	int hasline = FALSE;
	
	for (i = 0; i < m; i++) {
		
		for (j = 0; j < n; j++) {
			if (matrix[i][j] == array[j])  {
				counter++;
			}
		}
		if (counter == n) {
			hasline = TRUE;
			break;
		}
		counter = 0;
	}
	
	if (hasline)
		printf("A matriz possui uma linha igual ao vetor");
	else
		printf("A matriz NÃO possui uma linha que seja igual ao vetor");
	
	// b
	struct coord_value lower;
	
	for (i = 0; i < m; i++) {
		
		for (j = 0; j < n; j++) {
			
			if (matrix[i][j] < lower.value) {
				lower.value = matrix[i][j];
				lower.x = i;
				lower.y = j;
			}
		}
	}
	
	printf("O menor elemento da matriz é %d, na coluna %d, e linha %d", lower.value, lower.x, lower.y);
	return 0;
}

