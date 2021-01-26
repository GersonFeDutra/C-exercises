#include <stdio.h>
#include <locale.h>

#define FALSE 0
#define TRUE 1
#define ERRO -1 // Flag de Erro.

/* 1. Fa�a uma fun��o que receba como par�metros um vetor do tipo int e o tamanho desse
vetor. A fun��o deve retornar 1 caso o vetor seja um lecker e 0 caso contr�rio. Dizemos
que um vetor � lecker se ele tem apenas um elemento que � maior do que seus vizinhos.
Considere que o vetor ter� pelo menos 2 elementos. (2.0)
Exemplos:

 [2, 5, 10, 46, 25, 12, 7] � lecker, pois 46 � o �nico elemento que � maior que seus vizi-
nhos, que s�o 10 e 25.

 [13, 5, 4, 2, 3, 0] n�o � lecker, pois 13 � maior que 5 (5 � o �nico vizinho de 13) e 3 �
maior do que 2 e 0 (2 e 0 s�o vizinhos de 3).
 [4, 4, 4] n�o � lecker, pois n�o existe ningu�m que � maior do que os vizinhos.
 [4, 7] � lecker. */
int is_lecker(int arr[], int len) {
	int higher = 0, i;
	
	if (len < 2)
		return ERRO; // Por seguran�a
	
	for (i = 0; i < len; i++) {
		
		if (i == 0) {
			if (arr[0] > arr[1])
				higher++;
		}
		
		if (i == (len - 1)) {
			if (arr[i] > arr[i - 1]) {
				higher++;
			}
		}
		else {
			if (arr[i] > arr[i - 1] && arr[i] > arr[i + 1]) {
				higher++;
			}
		}
	}
	
	return (higher == 1);
}
 
 
int main() {
	void lecker_check(int* array, int size);
	setlocale(LC_ALL, "Portuguese");
	
	int arr1[] = {2, 5, 10, 46, 25, 12, 7};
	lecker_check(arr1, 7);
	
	
	int arr2[] = {13, 5, 4, 2, 3, 0};
	lecker_check(arr2, 6);
	
	int arr3[] = {4, 4, 4};
	lecker_check(arr3, 3);
	
	int arr4[] = {4, 7};
	lecker_check(arr4, 2);
	
	int len;
	printf("Quantos elementos deseja ler? ");
	
	while (TRUE) {
		scanf("%d", &len);
		
		if (len < 2)
			printf("A matriz deve ter mais que 2 elementos, por favor, tente novamente: ");
		else
			break;
	}
	
	int i;
	int array[len];
	
	for (i = 0; i < len; ++i) {
		printf("%d� = ", i + 1);
		scanf("%d", &array[i]);
	}
	lecker_check(array, len);
	
	return 0;
}


// Rotina de apoio que imprime as informa��s sobre se o array � lecker ou n�o.
void lecker_check(int* array, int size) {
	
	if (size < 0)
		printf("O tamanho n�o pode ser negativo!");
	
	printf("A matriz ");
	int i;
	
	printf("[%d", array[0]);
	for (i = 1; i < size; ++i) {
		printf(", %d", array[i]);
	}
	printf("] ");
	
	switch (is_lecker(array, size)) {
		case TRUE: printf("� lecker!\n"); break;
		case FALSE: printf("n�o � lecker!\n"); break;
		default: printf("n�o pode ser verificada.\n"); // ERRO
	}
}
