#include <stdio.h>
#include <locale.h>


/* 4. Faça um algoritmo que receba um número natural e imprima se ele é ou não triangular.
Um número natural é triangular se ele é produto de três números naturais consecutivos.
Exemplo: 120 é triangular, pois 4*5*6 = 120. O número 6 é triangular, já que 1*2*3 = 6. */
int main() {
	setlocale(LC_ALL, "Portuguese");
	
	int n, i, triangular = 0;
	printf("Digite um número natural: ");
	scanf("%d", &n);
	
	for (i = 1; i <= (n / 2.0); ++i) {
		
		if (((n % i) == 0) && ((i * (i + 1) * (i + 2)) == n)) {
			triangular = 1;
			break;
		}
	}
	
	if (triangular) {
		printf("%d é triangular.", n);
	}
	else {
		printf("%d não é triangular.", n);
	}
	
	return 0;
}

