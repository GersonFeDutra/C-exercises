#include <stdio.h>
#include <locale.h>


/* 3. Fa�a um programa que receba um n�mero n e preencha um vetor com n n�meros inteiros.
Em seguida, verifique e informe se o vetor est� em ordem crescente, decrescente, ou se ele
n�o satisfaz nenhuma estas condi��es. */
int main()
{
	setlocale(LC_ALL, "Portuguese");
	
	int n = 0, i, iscrescent, isdecrescent, isequal;
	iscrescent = isdecrescent = isequal = 1;
	
	printf("Quantos n�meros inteiros deseja analisar? ");
	
	while (1) {
		scanf("%d", &n);
		
		if (n <= 0) {
			printf("Erro! Por favor, insira um inteiro maior que 0: ");
		}
		else {
			break;
		}
	}
	
	// O valor de inicializa��o do vetor pode ser uma vari�vel.
	int arr[n]; // Assim o array pode ocupar espa�os maiores e de forma eficiente.
	//printf("%d", sizeof arr / sizeof(int)); // Teste -> Imprime o tamanho do array
	
	printf("\n1� = ");
	scanf("%d", &arr[0]);
	
	for (i = 1; i < n; ++i) {
		printf("%d� = ", i + 1);
		scanf("%d", &arr[i]);
		
		if (arr[i] < arr[i - 1]) { // Se decrescente.
			isequal = iscrescent = 0;
		}
		else if (arr[i] > arr[i - 1]) { // Se crescente.
			isequal = isdecrescent = 0;
		}
	}
	
	printf("O vetor [%d", arr[0]);
	
	for (i = 1; i < n; ++i)
		printf(", %d", arr[i]);
	
	printf("]\n");
	
	if		(n == 1) 	printf("Possui apenas 1 valor.");
	else if (isequal) 	printf("Possui valores iguais.");
	else if (iscrescent)	printf("Est� em ordem crescente.");
	else if (isdecrescent)	printf("Est� em ordem decrescente.");
	else
		printf("N�o est� em ordem crescente, nem decrescente.");
	
	return 0;
}

