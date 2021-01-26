#include <stdio.h>
#include <stdlib.h>
#include <locale.h>


/* 2. Sabendo que funções também podem retornar endereços de memória. Por exemplo, uma
função com a assinatura "int* gera_vetor(int n);"precisa retornar um endereço de memória
que armazena um número inteiro (ou o endereço inicial de um vetor do tipo inteiro).
Dada essa contextualização, faça uma função que receba um parâmetro inteiro n e aloca
na memória heap um vetor de n posições. Além disso, cada posição do vetor deve estar
relacionada com o número da sequência de Fibonacci daquela posição. Após isso, a função
deve retornar o endereço inicial do vetor.
Exemplo de vetor retornado para n = 3: [1, 1, 2]
Exemplo de vetor retornado para n = 6: [1, 1, 2, 3, 5, 8]
Exemplo de vetor retornado para n = 8: [1, 1, 2, 3, 5, 8, 13, 21] */
int* gera_vetor(int n) {
	void nacci(int *vetor, int size);
	
	int *vetor = (int*)malloc(sizeof(int) * n);
	
	if (n > 0) // Por segurança, não atribuir valor a um vetor vazio.
		vetor[0] = 1;
	
	if (n > 1) {
		vetor[1] = 1;
		nacci(vetor, n);
	}
	
	return vetor;
}

/* Essa função assume que você passou um vetor [1, 1, ...] e preenche o restante do vetor com
os números da sequência fibonacci. É apenas um segmento de `gera_vetor`, separado por motivos de organização. */
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
			printf("O número deve ser maior que %d.\nPor favor, tente novamente: ", n);
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

