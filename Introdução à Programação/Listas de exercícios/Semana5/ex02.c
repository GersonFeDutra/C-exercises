#include <stdio.h>
#include <locale.h>

#define ARRSIZE 10


/* 2. Fa�a um programa que recebe 10 n�meros inteiros e os armazene em um vetor. Calcule
e mostre:
(a) A quantidade de n�meros pares.
(b) A soma dos n�meros pares.
(c) A quantidade de n�meros �mpares.
(d) A soma dos n�meros �mpares.
*/
int main()
{
	setlocale(LC_ALL, "Portuguese");
	
	int array[ARRSIZE];
	int i, neven, sumeven, sumodd;
	neven = sumeven = sumodd = 0;
	
	printf("Insira 10 n�meros inteiros:\n");
	
	for (i = 0; i < ARRSIZE; ++i) {
		printf("%d� = ", i + 1);
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
	printf("(a) Quantidade de n�meros pares: %d\n", neven);
	printf("(b) Soma dos n�meros pares: %d\n", sumeven);
	printf("(c) Quantidade de n�meros �mpares: %d\n", ARRSIZE - neven);
	printf("(d) Soma dos n�meros �mpares: %d\n", sumodd);
	
	return 0;
}

