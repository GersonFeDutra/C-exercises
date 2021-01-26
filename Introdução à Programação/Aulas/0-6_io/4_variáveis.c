#include <stdio.h>


int main() {
	int idade; // Declaração
	idade = 32; // Atribuição
	printf("O valor da variavel eh: %d\n", idade); // Saída
	printf("Endereco da variavel `idade`: %d\n", &idade); // Referênciação
	printf("\n");
	
	int idade2 = 20;
	float altura = 1.69;
	char letra = 'c';
	printf("Valores: %d, %f, %c\n", idade2, altura, letra);
	printf("\n");
	int a, b;
	a = 3;
	b = 5;
	printf("Soma: %d\n", a + b);
	printf("Subtracao: %d\n", a - b);
	printf("Multiplicacao: %d\n", a * b);
	printf("Divisao (inteiros): %d\n", a / b);
	printf("\n");
	
	int divida = 0;
	int compra = 100;
	divida = divida + compra;
	compra = 200;
	divida += compra;
	compra = 300;
	divida += compra;
	printf("Divida: %d", divida);
	return 0;
}

