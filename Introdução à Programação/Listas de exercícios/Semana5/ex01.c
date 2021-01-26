#include <stdio.h>
#include <locale.h>

#define VECSIZE 10

/* 
--¦¦¦¦¦----_¦¦¦¦_-----
-¦-_¦-_¦--¦¦¦_¦¯------
-¦¦¦¦¦¦¦-¦¦¦¦¦--¦--¦--
-¦¦¦¦¦¦¦--¦¦¦¦¦_------
-¦-¦-¦-¦---¯¦¦¦¦¯-----
*/

/* 1. Faça um programa que preencha um vetor com 10 números. Depois, imprima o vetor
preenchido e informe o menor valor do vetor. */
int main()
{
	setlocale(LC_ALL, "Portuguese");
	
	float vector[VECSIZE], lower;
	int i;
	
	printf("Insira 10 números:\n1° = ");
	scanf("%f", &vector[0]);
	lower = vector[0];
	
	for (i = 1; i < VECSIZE; ++i) {
		printf("%d° = ", i + 1);
		scanf("%f", &vector[i]);
		
		if (vector[i] < lower)
			lower = vector[i];
	}
	
	printf("\n[%.2f", vector[0]); // Imprime o primeiro caractere sem espaço à esquerda.
	
	for (i = 1; i < VECSIZE; ++i)
		printf(", %.1f", vector[i]);
	
	printf("]\nMenor valor: %.1f", lower);
	
	return 0;
}

