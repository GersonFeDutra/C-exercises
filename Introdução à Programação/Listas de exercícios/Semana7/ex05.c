#include <stdio.h>
#include <locale.h>


/* 5. Crie um programa que contenha um vetor de inteiros contendo 5 elementos. Utilizando
apenas aritmética de ponteiros (ou seja, navegar o vetor utilizando a propriedade de
ponteiros), leia esse vetor do teclado e imprima o dobro de cada valor lido. */
int main() {
	setlocale(LC_ALL, "Portuguese");
	
	int i;
	int arr[5];
	
	printf("Digite 5 valores inteiros:\n");
	
	for (i = 0; i < 5; ++i) {
		printf("%c = ", 'a' + i);
		scanf("%d", (arr + i));
	}
	
	printf("\nO dobro dos respectivos números é:");
	
	for (i = 0; i < 5; ++i) {
		printf("\n%c -> %d", 'a' + i, 2 * *(arr + i));
	}
	
	return 0;
}

