#include <stdio.h>
#include <locale.h>


int main() {
	setlocale(LC_ALL, "Portuguese");
	
	int x;
	printf("Digite um número inteiro: ");
	scanf("%d", &x);
	
	if (x % 2 == 0) {
		printf("%d é par!", x);
	}
	else {
		printf("%d é ímpar!", x);
	}
	
	return 0;
}

