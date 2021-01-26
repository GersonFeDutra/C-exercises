#include <stdio.h>
#include <locale.h>


int main() {
	setlocale(LC_ALL, "Portuguese");

	float a, b;	
	printf("Digite um número qualquer: ");
	scanf("%f", &a);
	printf("Digite outro número: ");
	scanf("%f", &b);
	printf("\n%.2f * %.2f = %.2f", a, b, a * b);
	
	return 0;
}

