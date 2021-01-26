#include <stdio.h>


/* 1. Crie uma função que tenha como parâmetro uma variável do tipo float que indica uma
temperatura em Celsius. A função deve retornar o valor em Fahrenheit. Considere
F = (9 * °C / 5) + 32
float fahrenheit(float celsius); */
float fahrenheit(float celsius) {
	return (9.0 * celsius / 5.0) + 32;
}

