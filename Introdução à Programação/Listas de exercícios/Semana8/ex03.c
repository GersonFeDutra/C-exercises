#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "common.h" // Cont�m as fun��es gera_vetor() e get_higher_than() usadas entre m�ltiplas quest�es.


/* 3. Na fun��o principal (main), chame a fun��o gera_vetor (com n digitado pelo usu�rio),
armazene o vetor retornado em um ponteiro int* e imprima os seus elementos utilizando
aritm�tica de ponteiros. */
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

