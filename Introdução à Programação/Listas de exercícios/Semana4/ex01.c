#include <stdio.h>
#include <locale.h>


/* 1. Faça um algoritmo que receba um número digitado pelo usuário e imprima todos os
divisores do número. */
int main() {
	setlocale(LC_ALL, "Portuguese");
	
	int n, i;
	printf("Digite um número inteiro: ");
	scanf("%d", &n);
	printf("Divisores de %d: ", n);
	
	for (i = 1; i <= (n / 2); ++i)
	
		if ((n % i) == 0)
			printf("%d ", i);
	
	printf("%d", n);
	
	return 0;
}

