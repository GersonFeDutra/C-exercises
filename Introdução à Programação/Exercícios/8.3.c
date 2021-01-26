#include <stdio.h>
#include <locale.h>


int main() {
	setlocale(LC_ALL, "Portuguese");
	
	double n, i, factorial = 1;
	printf("Digite um número inteiro positivo: ");
	scanf("%lf", &n);
	
	for (i = n; i > 0; --i)
		factorial *= i;
	
	printf("%.0f! = %.0f", n, factorial);
	
	return 0;
}

