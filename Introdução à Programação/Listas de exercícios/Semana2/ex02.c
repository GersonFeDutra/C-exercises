#include <stdio.h>
#include <locale.h>


int main() {
	setlocale(LC_ALL, "Portuguese");

	float a, b;	
	printf("Digite um n�mero qualquer: ");
	scanf("%f", &a);
	printf("Digite outro n�mero: ");
	scanf("%f", &b);
	printf("\n%.2f * %.2f = %.2f", a, b, a * b);
	
	return 0;
}

