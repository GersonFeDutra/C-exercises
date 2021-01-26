#include <locale.h>

/* 1. Crie uma função que tenha como parâmetro uma variável do tipo float que indica uma
temperatura em Celsius. A função deve retornar o valor em Fahrenheit. Considere
F = (9 * °C / 5) + 32
float fahrenheit(float celsius); */
#include "ex01.h"


/* Usa a função `fahrenheit()` definida em "ex01.h" */
int main() {
	float fahrenheit(float celsius);
	setlocale(LC_ALL, "Portuguese");
	
	float celsius;
	printf("Insira um valor em °C: ");
	scanf("%f", &celsius);
	
	printf("%.1f°C em Fahrenheit é: %.1f", celsius, fahrenheit(celsius));
	
	return 0;
}

