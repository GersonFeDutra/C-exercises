#include <stdio.h>


/* 1. Crie uma fun��o que tenha como par�metro uma vari�vel do tipo float que indica uma
temperatura em Celsius. A fun��o deve retornar o valor em Fahrenheit. Considere
F = (9 * �C / 5) + 32
float fahrenheit(float celsius); */
float fahrenheit(float celsius) {
	return (9.0 * celsius / 5.0) + 32;
}

