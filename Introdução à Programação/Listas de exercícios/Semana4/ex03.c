#include <stdio.h>
#include <locale.h>


/* 3. Fa�a um algoritmo que receba dois n�meros inteiros positivos do usu�rio. O programa
deve calcular e exibir a multiplica��o dos dois n�meros. (N�o pode utilizar o operador de
multiplica��o *). */
int main() {
	setlocale(LC_ALL, "Portuguese");
	
	int a, b, product = 0, i;
	a = b = -1;
	
	while (a < 0) {
		printf("Digite um n�mero inteiro positivo: ");
		scanf("%d", &a);
	}
	
	while (b < 0) {
		printf("Digite outro n�mero inteiro positivo: ");
		scanf("%d", &b);
	}
	
	for (i = 0; i < b; ++i) {
		product += a;
	}
	
	printf("%d x %d = %d", a, b, product);
	
	return 0;
}

