#include <stdio.h>
#include <locale.h>


/* 2. Escreva um programa que contenha duas variaveis inteiras. Compare seus enderešos e
exiba o maior enderešo. */
int main() {
	setlocale(LC_ALL, "Portuguese");
	
	int a = 1, b = 2;
	printf("Maior enderešo: %d", &a > &b ? &a : &b);
	
	return 0;
}

