#include <stdio.h>
#include <stdlib.h>
#include <locale.h>


/* 2. Sabendo que fun��es tamb�m podem retornar endere�os de mem�ria. Por exemplo, uma
fun��o com a assinatura "int* gera_vetor(int n);"precisa retornar um endere�o de mem�ria
que armazena um n�mero inteiro (ou o endere�o inicial de um vetor do tipo inteiro).
Dada essa contextualiza��o, fa�a uma fun��o que receba um par�metro inteiro n e aloca
na mem�ria heap um vetor de n posi��es. Al�m disso, cada posi��o do vetor deve estar
relacionada com o n�mero da sequ�ncia de Fibonacci daquela posi��o. Ap�s isso, a fun��o
deve retornar o endere�o inicial do vetor.
Exemplo de vetor retornado para n = 3: [1, 1, 2]
Exemplo de vetor retornado para n = 6: [1, 1, 2, 3, 5, 8]
Exemplo de vetor retornado para n = 8: [1, 1, 2, 3, 5, 8, 13, 21] */
int* gera_vetor(int n) {
	void nacci(int *vetor, int size);
	
	int *vetor = (int*)malloc(sizeof(int) * n);
	
	if (n > 0) // Por seguran�a, n�o atribuir valor a um vetor vazio.
		vetor[0] = 1;
	
	if (n > 1) {
		vetor[1] = 1;
		nacci(vetor, n);
	}
	
	return vetor;
}

/* Essa fun��o assume que voc� passou um vetor [1, 1, ...] e preenche o restante do vetor com
os n�meros da sequ�ncia fibonacci. � apenas um segmento de `gera_vetor`, separado por motivos de organiza��o. */
void nacci(int *vetor, int size) {
	int i;
	
	for (i = 2; i < size; ++i) {
		vetor[i] = vetor[i - 1] + vetor[i - 2];
	}
}

int main() {
	int get_higher_than(int);
	setlocale(LC_ALL, "Portuguese");
	
	printf("Digite o tamanho do vetor: ");
	
	int n = get_higher_than(-1);
	int *vetor = gera_vetor(n);
	
	print_array(vetor, n);
	
	return 0;
}

int get_higher_than(int n) {
	while (1) {
		int x;
		scanf("%d", &x);
		
		if (x > n)
			return x;
		else
			printf("O n�mero deve ser maior que %d.\nPor favor, tente novamente: ", n);
	}
}

int print_array(int *array, int size) {
	int i;
	printf("[");
	
	if (size > 0)
		printf("%d", array[0]);
	
	for (i = 1; i < size; ++i) {
		printf(", %d", array[i]);
	}
	printf("]");
}

