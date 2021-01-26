#include <stdio.h>
#include <locale.h>


/* 4. Fa�a um algoritmo que receba um n�mero natural e imprima se ele � ou n�o triangular.
Um n�mero natural � triangular se ele � produto de tr�s n�meros naturais consecutivos.
Exemplo: 120 � triangular, pois 4*5*6 = 120. O n�mero 6 � triangular, j� que 1*2*3 = 6. */
int main() {
	setlocale(LC_ALL, "Portuguese");
	
	int n, i, triangular = 0;
	printf("Digite um n�mero natural: ");
	scanf("%d", &n);
	
	for (i = 1; i <= (n / 2.0); ++i) {
		
		if (((n % i) == 0) && ((i * (i + 1) * (i + 2)) == n)) {
			triangular = 1;
			break;
		}
	}
	
	if (triangular) {
		printf("%d � triangular.", n);
	}
	else {
		printf("%d n�o � triangular.", n);
	}
	
	return 0;
}

