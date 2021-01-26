#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "common.h" // Contém as funções gera_vetor() e get_higher_than() usadas entre múltiplas questões.


/* 3. Na função principal (main), chame a função gera_vetor (com n digitado pelo usuário),
armazene o vetor retornado em um ponteiro int* e imprima os seus elementos utilizando
aritmética de ponteiros. */
int main() {
	int* gera_vetor(int n);
	int get_higher_than(int n);
	setlocale(LC_ALL, "Portuguese");
	
	printf("Digite o tamanho do vetor: ");
	int i, n = get_higher_than(-1);
	int *vetor = gera_vetor(n);
	
	printf("[");
	
	if (n > 0)
		printf("%d", *(vetor));
	
	for (i = 1; i < n; ++i) {
		printf(", %d", *(vetor + i));
	}
	
	printf("]");
	
	return 0;
}

