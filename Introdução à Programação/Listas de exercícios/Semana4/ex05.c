#include <stdio.h>
#include <locale.h>


/* 5. Faça um programa que receba um número inteiro do usuário (maior do que 1) e imprima
se ele é primo ou não. */
int main() {
	setlocale(LC_ALL, "Portuguese");
	
	int n = 0, i, isprime = 1;
	
	while (n <= 1) {
		printf("Digite um número inteiro (maior que 1): ");
		scanf("%d", &n);	
	}
	
	for (i = 2; i <= (n / 2.0); ++i) {
		
		if ((n % i) == 0) {
			isprime = 0;
			break;
		}
	}
	
	if (isprime)
		printf("%d é primo.", n);
	else
		printf("%d não é primo.", n);
	
	return 0;
}

