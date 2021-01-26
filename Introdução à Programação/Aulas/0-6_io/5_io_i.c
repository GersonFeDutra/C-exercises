#include <stdio.h>


int main() {
	int a;
	printf("Digite um numero inteiro: ");
	scanf("%d", &a);
	printf("Numero digitado: %d\n", a);
	printf("\n");
	
	int numero;
	char letra;
	printf("Digite um numero inteiro e uma letra: ");
	scanf("%d %c", &numero, &letra);
	printf("Valores digitados: %d e %c", numero, letra);
	return 0;
}

