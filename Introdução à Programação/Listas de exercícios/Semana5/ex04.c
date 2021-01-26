#include <stdio.h>
#include <locale.h>


/* 4. Fa�a um programa que receba um n�mero n e preencha um vetor com n n�meros inteiros.
Em seguida, imprima o vetor na ordem inversa. Ex: n:3, Vetor: [4,76,9] � Ordem de
Impress�o: [9,76,4]. */
int main()
{
	setlocale(LC_ALL, "Portuguese");
	
	int n = 0, i;
	
	/* Entrada do valor n */
	printf("Quantos n�meros (inteiros) deseja inserir? ");
	
	while (1) {
		scanf("%d", &n);
		
		if (n <= 0) {
			printf("Erro! Por favor, insira um inteiro maior que 0: ");
		}
		else {
			break;
		}
	}
	
	/* Cria��o do vetor */
	int arr[n]; // O valor de inicializa��o do vetor pode ser uma vari�vel.
	
	printf("\n1� = ");
	scanf("%d", &arr[0]);
	
	for (i = 1; i < n; ++i) {
		printf("%d� = ", i + 1);
		scanf("%d", &arr[i]);
		
	}
	
	/* Sa�da */
	printf("A ordem inversa desse vetor �: [%d", arr[n - 1]);
	
	for (i = n - 2; i >= 0; --i)
		printf(", %d", arr[i]);
	
	printf("]");
	
	return 0;
}

