#include <stdio.h>
#include <locale.h>


int main() {
	setlocale(LC_ALL, "Portuguese");
	
	int a, b, product, i;
	
	printf("Digite um n�mero inteiro positivo: ");
	scanf("%d", &a);
	
	printf("Digite outro n�mero inteiro positivo: ");
	scanf("%d", &b);
	
	printf("%d", a);
	product = a;
	
	for (i; i < b; ++i) {
		product += a;
		printf(" + %d", a);
	}
	
	printf(" = %d", product);
	
	return 0;
}

