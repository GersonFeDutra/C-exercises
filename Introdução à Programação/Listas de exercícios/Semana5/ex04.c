#include <stdio.h>
#include <locale.h>


/* 4. Faça um programa que receba um número n e preencha um vetor com n números inteiros.
Em seguida, imprima o vetor na ordem inversa. Ex: n:3, Vetor: [4,76,9] – Ordem de
Impressão: [9,76,4]. */
int main()
{
	setlocale(LC_ALL, "Portuguese");
	
	int n = 0, i;
	
	/* Entrada do valor n */
	printf("Quantos números (inteiros) deseja inserir? ");
	
	while (1) {
		scanf("%d", &n);
		
		if (n <= 0) {
			printf("Erro! Por favor, insira um inteiro maior que 0: ");
		}
		else {
			break;
		}
	}
	
	/* Criação do vetor */
	int arr[n]; // O valor de inicialização do vetor pode ser uma variável.
	
	printf("\n1° = ");
	scanf("%d", &arr[0]);
	
	for (i = 1; i < n; ++i) {
		printf("%d° = ", i + 1);
		scanf("%d", &arr[i]);
		
	}
	
	/* Saída */
	printf("A ordem inversa desse vetor é: [%d", arr[n - 1]);
	
	for (i = n - 2; i >= 0; --i)
		printf(", %d", arr[i]);
	
	printf("]");
	
	return 0;
}

