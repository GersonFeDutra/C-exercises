#include <stdio.h>
#include <locale.h>


/* 3. Fa�a um algoritmo que leia o valor de duas vari�veis inteiras (digitadas pelo usu�rio). Em
seguida, compare seus endere�os e imprima o conte�do da vari�vel que possui o maior
endere�o */
int main() {
	setlocale(LC_ALL, "Portuguese");
	
	int a = 1, b = 2;
	printf("Valor da vari�vel de maior endere�o: %d", &a > &b ? a : b);
	
	return 0;
}

