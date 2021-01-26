#include <stdio.h>
#include <locale.h>


/* 6. Faça uma função que receba dois valores inteiros (como parâmetros) e retorne o maior
dos dois números. */
int higher(int a, int b) {
	return a > b ? a : b;
}

int main() {
	setlocale(LC_ALL, "Portuguese");
	
	int a, b;
	printf("Insira dois valores inteiros:\na = ");
	scanf("%d", &a);
	
	printf("b = ");
	scanf("%d", &b);
	
	printf("O maior valor é %d.", higher(a, b));
	
	return 0;
}

