#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "common.h" // Cont�m as fun��es gera_vetor(), get_higher_than() e print_array() usadas entre m�ltiplas quest�es.


/* 5. Imprima os valores do novo vetor (ap�s o relloc). Ap�s isso, libere o vetor da mem�ria e
encerre o programa. */
int main() {
	int* gera_vetor(int n);
	int get_higher_than(int n);
	int print_array(int *array, int size);
	setlocale(LC_ALL, "Portuguese");
	
	printf("Determine o tamanho do vetor: ");
	int i, n = get_higher_than(-1);
	int *vetor = gera_vetor(n);
	
	printf("Antes: ");
	print_array(vetor, n);
	
	int doublen = n * 2;
	vetor = (int*)realloc(vetor, sizeof(int) * doublen);
	
	for (i = n; i < doublen; ++i)
		vetor[i] = vetor[i - n] * 3;
	
	printf("\nDepois: ");
	print_array(vetor, doublen);
	
	// Limpa o vetor da mem�ria
	free(vetor);
	vetor = NULL;
	
	return 0;
}

