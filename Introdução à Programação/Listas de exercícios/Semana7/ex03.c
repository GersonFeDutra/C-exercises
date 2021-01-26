#include <stdio.h>
#include <locale.h>


/* 3. Faça um algoritmo que leia o valor de duas variáveis inteiras (digitadas pelo usuário). Em
seguida, compare seus endereços e imprima o conteúdo da variável que possui o maior
endereço */
int main() {
	setlocale(LC_ALL, "Portuguese");
	
	int a = 1, b = 2;
	printf("Valor da variável de maior endereço: %d", &a > &b ? a : b);
	
	return 0;
}

