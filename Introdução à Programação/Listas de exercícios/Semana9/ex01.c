#include <locale.h>

/* 1. Crie uma fun��o que tenha como par�metro uma vari�vel do tipo float que indica uma
temperatura em Celsius. A fun��o deve retornar o valor em Fahrenheit. Considere
F = (9 * �C / 5) + 32
float fahrenheit(float celsius); */
#include "ex01.h"


/* Usa a fun��o `fahrenheit()` definida em "ex01.h" */
int main() {
	float fahrenheit(float celsius);
	setlocale(LC_ALL, "Portuguese");
	
	float celsius;
	printf("Insira um valor em �C: ");
	scanf("%f", &celsius);
	
	printf("%.1f�C em Fahrenheit �: %.1f", celsius, fahrenheit(celsius));
	
	return 0;
}

