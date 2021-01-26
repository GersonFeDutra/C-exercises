#include <stdio.h>
#include <locale.h>


/* 6. Crie um programa que contenha um vetor de inteiros contendo 7 elementos. Utilizando
apenas aritmética de ponteiros (ou seja, navegar o vetor utilizando a propriedade de
ponteiros), leia esse vetor do teclado e imprima a soma dos elementos que estão em posição
par. */
int main() {
	setlocale(LC_ALL, "Portuguese");
	
	int i, evensum = 0;
	int arr[7];
	
	printf("Digite 7 valores inteiros:\n");
	
	for (i = 0; i < 7; ++i) {
		printf("[%d] = ", i);
		scanf("%d", (arr + i));
		
		if (i % 2 == 0)
			evensum += *(arr + i);
	}
	
	printf("A soma dos elementos em posições (índices) pares é: %d", evensum);
	
	return 0;
}

