#include <stdio.h>
#include <locale.h>


/* 6. Fa�a uma fun��o que receba dois valores inteiros (como par�metros) e retorne o maior
dos dois n�meros. */
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
	
	printf("O maior valor � %d.", higher(a, b));
	
	return 0;
}

