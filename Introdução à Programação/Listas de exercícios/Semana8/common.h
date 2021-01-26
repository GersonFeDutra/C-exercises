#include <stdio.h>
#include <stdlib.h>

/* Esse arquivo contém algumas funções comuns usadas durante o exercício.
A primeira aparição da definição dessas funções continuará presente na
questão original. */


int* gera_vetor(int n) {
	void nacci(int *vetor, int size);
	
	int *vetor = (int*)malloc(sizeof(int) * n);
	
	if (n > 0) // Por segurança, não atribuir valor a um vetor vazio.
		vetor[0] = 1;
	
	if (n > 1) {
		vetor[1] = 1;
		nacci(vetor, n);
	}
	
	return vetor;
}

/* Essa função assume que você passou um vetor [1, 1, ...] e preenche o restante do vetor com
os números da sequência fibonacci. É apenas um segmento de `gera_vetor`, separado por motivos
de organização. */
void nacci(int *vetor, int size) {
	int i;
	
	for (i = 2; i < size; ++i) {
		vetor[i] = vetor[i - 1] + vetor[i - 2];
	}
}

int get_higher_than(int n) {
	while (1) {
		int x;
		scanf("%d", &x);
		
		if (x > n)
			return x;
		else
			printf("O número deve ser maior que %d.\nPor favor, tente novamente: ", n);
	}
}

int print_array(int *array, int size) {
	int i;
	printf("[");
	
	if (size > 0)
		printf("%d", array[0]);
	
	for (i = 1; i < size; ++i) {
		printf(", %d", array[i]);
	}
	printf("]");
}

