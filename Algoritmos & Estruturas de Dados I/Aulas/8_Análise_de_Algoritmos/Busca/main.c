#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/* Busca em um vetor ordenado de forma inteligente.
Vantagens: Muito rápida, especialmente para muitos dados.
Desvantagens: Requer que o vetor esteja ordenado. */
int busca_binaria(int *vetor, unsigned int n, int x)
{
	int inicio = 0, meio, fim = n - 1;

	while (inicio <= fim) {
		meio = floor((inicio + fim) / 2);

		if (x < vetor[meio])
			fim = meio - 1;
		else if (x > vetor[meio])
			inicio = meio + 1;
		else
			return meio;
	}

	return -1;
}

/* Busca Binária.
Versão alternativa/ aprimorada do modelo acima */
int busca_binaria2(int *vetor, unsigned int n, int x)
{
	int inicio = 0, fim = n - 1;

	while (inicio < fim) {
		int meio = (inicio + fim) / 2;

		if (x < vetor[meio])
			fim = meio - 1;
		else if (x > vetor[meio])
			inicio = meio + 1;
		else
			return meio;
	}
	if (x == vetor[fim])
		return fim;

	return -1;
}


/* Busca Binária.
Versão alternativa do modelo acima usando o tamanho do array como flag de falha.
Note que n deve ser maior que 0. */
// unsigned int busca_binaria3(int *vetor, unsigned int n, int x)
// {
// 	// if (n == 0)
// 	// 	return 0;
// 
// 	unsigned int inicio = 0, fim = n - 1;
// 
// 	while (inicio < fim) {
// 		unsigned int meio = (inicio + fim) / 2;
// 
// 		if (x < vetor[meio])
// 			fim = meio - 1;
// 		else if (x > vetor[meio])
// 			inicio = meio + 1;
// 		else
// 			return meio;
// 	}
// 	if (x == vetor[fim])
// 		return fim;
// 
// 	return n;
// }


/* Busca em um vetor ordenado. O(1) - O(n)
Vantagens: Pode parar antes de andar o vetor todo.
Desvantagens: Requer que o vetor esteja ordenado. */
int busca_sequencial_ordenada(int *vetor, unsigned int tamanho, int x)
{
	int i;

	for (i = 0; i < tamanho; ++i)
		if (vetor[i] == x)
			return i;
		else if (vetor[i] > x)
			return -1;

	return -1;
}


/* Busca mais simples que existe. O(1) - O(n)
Vantagens: Não requer que os dados sejam ordenados.
Desvantagens: Demora muito. */
int busca_sequencial(int *vetor, unsigned int tamanho, int x)
{
	int i;

	for (i = 0; i < tamanho; ++i)
		if (vetor[i] == x)
			return i;

	return -1;
}


/* Programa que testa o tempo de execução dos diferentes algoritmos de busca. */
int main()
{
	void imprimir_duracao(clock_t inicio, clock_t fim);
	setlocale(LC_ALL, "Portuguese");

	struct busca {
		char *mensagem;
		int (*tipo)(int *vetor, unsigned int tamanho, int x);
	} typedef Busca;

	static const unsigned int BUSCAS = 4;
	static const unsigned int TAMANHO = 1999999;
	static const unsigned int RANGE = TAMANHO / 100;

	clock_t inicio, fim;
	unsigned int i, vetor[TAMANHO];
	/* Armazenamos os mesmos valores aleatórios para usarmos nos algoritmos de busca. */
	int valores_buscados[RANGE];
	// int n = rand() % RANGE;

	Busca buscas[] = {
		{.mensagem = "Busca sequencial", .tipo = &busca_sequencial},
		{.mensagem = "Busca sequencial ordenada", .tipo = &busca_sequencial_ordenada},
		{.mensagem = "Busca binária", .tipo = &busca_binaria},
		{.mensagem = "Busca binária 2", .tipo = &busca_binaria2},
	};

	// Cria um vetor aleatório para ser usado nas buscas.
	// for (i = 0; i < TAMANHO; ++i)
	// vetor[i] = rand() % RANGE;

	// Cria um vetor ordenado - para ser usado nas buscas ordenadas.
	for (i = 0; i < TAMANHO; ++i)
		vetor[i] = i;

	for (i = 0; i < RANGE; ++i)
		valores_buscados[i] = rand() % RANGE;

	// Loop que testa nossos algoritmos de busca.
	for (i = 0; i < BUSCAS; ++i) {
		int pos, j;
		printf("%s: ", buscas[i].mensagem);

		inicio = clock();

		for (j = 0; j < RANGE; ++j)
			pos = buscas[i].tipo(vetor, TAMANHO, valores_buscados[j]);

		fim = clock();

		// if (pos == -1)
		// 	printf("Valor não foi encontrado!\n");
		// else
		// 	printf("%d encontrado na %d° posição do array!\n", n, pos);

		imprimir_duracao(inicio, fim);
	}

	return 0;
}


void imprimir_duracao(clock_t inicio, clock_t fim)
{
	unsigned long int dif = (fim - inicio);
	unsigned long int duracao = dif * 1000 / CLOCKS_PER_SEC; // Regularização do clock.

	printf("Executado em %lu ms.\n", duracao);
	// printf("Diferença de %lu clocks\n", dif);
}
