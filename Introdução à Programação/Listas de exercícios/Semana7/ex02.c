#include <stdio.h>
#include <locale.h>


/* 2. Escreva um programa que contenha duas variaveis inteiras. Compare seus endere�os e
exiba o maior endere�o. */
int main() {
	setlocale(LC_ALL, "Portuguese");
	
	int a = 1, b = 2;
	printf("Maior endere�o: %d", &a > &b ? &a : &b);
	
	return 0;
}

