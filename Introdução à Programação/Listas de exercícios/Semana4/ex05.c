#include <stdio.h>
#include <locale.h>


/* 5. Fa�a um programa que receba um n�mero inteiro do usu�rio (maior do que 1) e imprima
se ele � primo ou n�o. */
int main() {
	setlocale(LC_ALL, "Portuguese");
	
	int n = 0, i, isprime = 1;
	
	while (n <= 1) {
		printf("Digite um n�mero inteiro (maior que 1): ");
		scanf("%d", &n);	
	}
	
	for (i = 2; i <= (n / 2.0); ++i) {
		
		if ((n % i) == 0) {
			isprime = 0;
			break;
		}
	}
	
	if (isprime)
		printf("%d � primo.", n);
	else
		printf("%d n�o � primo.", n);
	
	return 0;
}

