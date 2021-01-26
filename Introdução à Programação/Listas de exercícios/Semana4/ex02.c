#include <stdio.h>
#include <locale.h>


/* 2. Faça um algoritmo que receba um número n do usuário e calcule o valor da série S dos n
primeiros termos da série: S = 1/1 - 2/4 + 3/9 - 4/16 + 5/25 */
int main() {
	setlocale(LC_ALL, "Portuguese");
	
	int n, i, i_square;
	float sum = 0.0;
	printf("Digite um número inteiro: ");
	scanf("%d", &n);
	
	if (n > 0) {
		printf("S = 1/1");
		sum = 1;
	}
	
	for (i = 2; i <= n; ++i) {
		i_square = i * i;
		
		if ((i % 2 == 0)) {
			printf(" - %d/%d", i, i_square);
			sum -= i / (float) i_square;
		}
		else {
			printf(" + %d/%d", i, i_square);
			sum += i / (float) i_square;
		}
	}
	
	printf("\nS = %.3f", sum);
	
	return 0;
}

