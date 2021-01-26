#include <stdio.h>
#include <locale.h>


/* 3. Faça um algoritmo que receba dois números inteiros positivos do usuário. O programa
deve calcular e exibir a multiplicação dos dois números. (Não pode utilizar o operador de
multiplicação *). */
int main() {
	setlocale(LC_ALL, "Portuguese");
	
	int a, b, product = 0, i;
	a = b = -1;
	
	while (a < 0) {
		printf("Digite um número inteiro positivo: ");
		scanf("%d", &a);
	}
	
	while (b < 0) {
		printf("Digite outro número inteiro positivo: ");
		scanf("%d", &b);
	}
	
	for (i = 0; i < b; ++i) {
		product += a;
	}
	
	printf("%d x %d = %d", a, b, product);
	
	return 0;
}

