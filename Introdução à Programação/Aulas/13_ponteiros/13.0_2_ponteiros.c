#include <stdio.h>
#include <locale.h>


int main() {
	setlocale(LC_ALL, "Portuguese");

	int a, b;
	
	printf("Insira dois valores inteiros:\n");
	scanf("%d %d", &a, &b);
	
	printf("O valor da vari�vel de maior endere�o: %d", &a > &b ? a : b);

	return 0;
}
