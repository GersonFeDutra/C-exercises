#include <stdio.h>
#include <locale.h>


/* 1. Fa�a um algoritmo que receba um n�mero digitado pelo usu�rio e imprima todos os
divisores do n�mero. */
int main() {
	setlocale(LC_ALL, "Portuguese");
	
	int n, i;
	printf("Digite um n�mero inteiro: ");
	scanf("%d", &n);
	printf("Divisores de %d: ", n);
	
	for (i = 1; i <= (n / 2); ++i)
	
		if ((n % i) == 0)
			printf("%d ", i);
	
	printf("%d", n);
	
	return 0;
}

