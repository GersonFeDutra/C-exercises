#include <stdio.h>
#include <locale.h>


int main() {
	setlocale(LC_ALL, "Portuguese");

	int a, b;
	
	printf("Insira dois valores inteiros:\n");
	scanf("%d %d", &a, &b);
	
	printf("O valor da variável de maior endereço: %d", &a > &b ? a : b);

	return 0;
}
