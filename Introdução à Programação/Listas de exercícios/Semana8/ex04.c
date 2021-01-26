#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "common.h"  // Cont�m as fun��es gera_vetor(), get_higher_than() e print_array() usadas entre m�ltiplas quest�es.


/* 4. Na fun��o principal (main), utilize a fun��o realloc para aumentar a quantidade de
posi��es do vetor. Nesse caso, o vetor ter� duas vezes o seu tamanho original. Nas
posi��es novas do vetor, espelhe as posi��es originais de tal forma que as novas posi��es
tenham 3 vezes o valor das posi��es originais.
Exemplos:
O vetor [1, 1, 2], depois do realloc, dever� ter os elementos: [1, 1, 2, 3, 3, 6].
O vetor [1, 1, 2, 3], depois do realloc, dever� ter os elementos: [1, 1, 2, 3, 3, 3, 6, 9].
O vetor [1, 1, 2, 3, 5], depois do realloc, dever� ter os elementos:
[1, 1, 2, 3, 5, 3, 3, 6, 9, 15] */
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
	
	return 0;
}

