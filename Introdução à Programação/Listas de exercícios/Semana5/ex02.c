#include <stdio.h>
#include <locale.h>

#define ARRSIZE 10


/* 2. Faça um programa que recebe 10 números inteiros e os armazene em um vetor. Calcule
e mostre:
(a) A quantidade de números pares.
(b) A soma dos números pares.
(c) A quantidade de números ímpares.
(d) A soma dos números ímpares.
*/
int main()
{
	setlocale(LC_ALL, "Portuguese");
	
	int array[ARRSIZE];
	int i, neven, sumeven, sumodd;
	neven = sumeven = sumodd = 0;
	
	printf("Insira 10 números inteiros:\n");
	
	for (i = 0; i < ARRSIZE; ++i) {
		printf("%d° = ", i + 1);
		scanf("%d", &array[i]);
		
		if (array[i] % 2 == 0) {
			++neven;
			sumeven += array[i];
		}
		else {
			sumodd += array[i];
		}
	}
	
	printf("\n");
	printf("(a) Quantidade de números pares: %d\n", neven);
	printf("(b) Soma dos números pares: %d\n", sumeven);
	printf("(c) Quantidade de números ímpares: %d\n", ARRSIZE - neven);
	printf("(d) Soma dos números ímpares: %d\n", sumodd);
	
	return 0;
}

