#include <stdio.h>
#include <locale.h>

#define ERRMESSAGE "Nota inv�lida.\nTente novamente: "

/* 6. Fa�a um programa que receba 3 notas de um aluno e mostre a m�dia. O programa deve
ter valida��o de notas. Ou seja, se uma nota digitada for menor que 0 ou maior que 10, o
programa deve informar "nota inv�lida"e pedir para o usu�rio digitar a nota novamente. */
int main() {
	setlocale(LC_ALL, "Portuguese");
	
	float a, b, c;
	printf("Digite tr�s notas (0-10)\n1� ");
	
	while (1) { // Que agonia n�o poder usar fun��es/ arrays nesses exerc�cios :P
		scanf("%f", &a);
		
		if (a >= 0 && a <= 10)
			break;
		else
			printf(ERRMESSAGE);
	}
	
	printf("2� ");
	
	while (1) {
		scanf("%f", &b);
		
		if (b >= 0 && b <= 10)
			break;
		else
			printf(ERRMESSAGE);
	}
	
	printf("3� ");
	
	while (1) {
		scanf("%f", &c);
		
		if (c >= 0 && c <= 10)
			break;
		else
			printf(ERRMESSAGE);
	}
	
	printf("A m�dia do aluno foi de: %.1f", (a + b + c) / 3);
	
	return 0;
}

