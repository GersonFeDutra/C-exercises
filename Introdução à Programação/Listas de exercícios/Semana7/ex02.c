#include <stdio.h>
#include <locale.h>


/* 2. Escreva um programa que contenha duas variaveis inteiras. Compare seus endereços e
exiba o maior endereço. */
int main() {
	setlocale(LC_ALL, "Portuguese");
	
	int a = 1, b = 2;
	printf("Maior endereço: %d", &a > &b ? &a : &b);
	
	return 0;
}

