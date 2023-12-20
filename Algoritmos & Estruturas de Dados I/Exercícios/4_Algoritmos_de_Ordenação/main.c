#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void quick_sort(int *array, unsigned int size);
void insertion_sort(int *array, unsigned int size);
void insertion_sort_wh_cache(int *array, unsigned int size);
void insertion_sort_wh_swap(int *array, unsigned int size);
void quick_sort(int *array, unsigned int size);
void quick_sort_wh_swap(int *array, unsigned int size);
void _swap(int *a, int *b);


/* Programa que testa o tempo de execução dos diferentes algoritmos de ordenação. */
int main()
{
	void print_duration(clock_t start, clock_t end);
	setlocale(LC_ALL, "Portuguese");

	struct sort_algorithm {
		char *message;
		void (*type)(int *array, unsigned int size);
	} typedef Busca;

	static const unsigned int SORT_ALGORITHMS = 5;
	static const unsigned int SIZE = 39999;
	static const unsigned int RANGE = SIZE;

	clock_t start, end;
	unsigned int i, base_array[SIZE], copy_array[SIZE];
	/* Usamos uma cópia do array para obtermos os mesmos valores aleatórios a serem usados nos
	algoritmos de ordenação. */

	Busca sort_algorithms[] = {
		{.message = "Ordenação por inserção", .type = &insertion_sort},
		{.message = "Ordenação por inserção 2", .type = &insertion_sort_wh_cache},
		{.message = "Ordenação por inserção (usando função swap)", .type = &insertion_sort_wh_swap},
		{.message = "Ordenação rápida", .type = &quick_sort},
		{.message = "Ordenação rápida (usando função swap)", .type = &quick_sort_wh_swap},
	};

	for (i = 0; i < SIZE; ++i)
		base_array[i] = rand() % RANGE;

	printf("Iniciando ordenações...\n");
	// Loop que testa nossos algoritmos de ordenação.
	for (i = 0; i < SORT_ALGORITHMS; ++i) {
		int j;

		for (j = 0; j < SIZE; ++j)
			copy_array[j] = base_array[j];

		printf("%s: ", sort_algorithms[i].message);

		start = clock();
		sort_algorithms[i].type(copy_array, SIZE);
		end = clock();

		print_duration(start, end);

		// for (j = 0; j < SIZE; ++j)
		// 	printf("%d ", copy_array[j]);
		// printf("\n\n");
	}

	return 0;
}


/* Um dos mais simples algoritmos de ordenação. O(n) - O(n²)
0. Percorre o array da direita para a esquerda (do segundo ao último);
1. Examina cada ítem (do índice atual ao primeiro) com o ítem a sua esquerda;
2. Insere os ítens em suas posições corretas no array.
*/
void insertion_sort(int *array, unsigned int size)
{
	// Referências: <https://youtu.be/JU767SDMDvA> <https://youtu.be/S5no2qT8_xg>
	int i;

	for (i = 1; i < size; ++i) {
		int j = i;

		while (j > 0 && array[j - 1] > array[j]) {
			int swap = array[j];
			array[j] = array[j - 1];
			array[j - 1] = swap;
			--j;
		}
	}
}


/* Versão um pouco melhorada do insertion sort, com cache na operação de subtração. */
void insertion_sort_wh_cache(int *array, unsigned int size)
{
	int i;

	for (i = 1; i < size; ++i) {
		int j = i;
		register int lj = j - 1;

		while (j > 0 && array[lj] > array[j]) {
			int swap = array[j];
			array[j] = array[lj];
			array[lj] = swap;
			j = lj;
			--lj;
		}
	}
}


void insertion_sort_wh_swap(int *array, unsigned int size)
{
	int i;

	for (i = 1; i < size; ++i) {
		int j = i;
		int lj = j - 1;

		while (j > 0 && array[lj] > array[j]) {
			_swap(&array[j], &array[lj]);
			j = lj;
			--lj;
		}
	}
}

/* Um dos melhores algoritmos de ordenação. O(n log(n)) - O(n log(n)) - O(n²)
Usa o método recursivo.
Usamos um pivot (âncora), que será um ítem do array que segue as seguintes condições após ordená-lo:
0. Está na sua posição final de ordenação;
1. Ítens da esquerda são menores;
2. Ítens da direita são maiores.

0. Escolhemos uma âncora, e o movemos para o final do array;
1. Procuramos 2 ítens;
- Ítem da esquerda: Primeiro ítem da esquerda que é maior que a âncora;
- Ítem da direita: Primeiro ítem da direita que é menor que a âncora;
2. Fazemos o swap (troca) desses ítens;
3. Iteramos até que o ítem da esquerda for _maior_ que o ítem da direita;
4. Fazemos o swap do último ítem da esquerda com a âncora;
Ao fazer isso a nossa âncora estará seguindo as 3 condições determinadas.
5. Criamos partições com base na âncora e repetimos o processo.

* Para escolher a âncora usamos um método chamado de "Medium of three":
0. Olhamos os ítens do centro, início e fim;
1. Ordenamos esses 3 ítens;
2. Escolhemos o novo elemento central como a âncora.
Por meio desse método, assumimos que o novo elemento central é próximo da média do nosso array.
*/
void quick_sort(int *array, unsigned int size)
{
	// Essa é a função de inicialização do algoritmo, a sua implementação está no método, de
	// mesmo nome, abaixo.
	void _quick_sort(int *array, int low, int high);
	_quick_sort(array, (int)0, (int)(size - 1));
}


/* Função auxiliar do `_quick_sort`. */
int partition(int *array, int low, int high)
{
	int i, pivot = array[high], swap;
	int left_wall = low;

	for (i = low; i < high; ++i)

		if (array[i] < pivot) {
			swap = array[i];
			array[i] = array[left_wall];
			array[left_wall] = swap;
			++left_wall;
		}

	swap = array[i];
	array[i] = array[left_wall];
	array[left_wall] = swap;

	return left_wall;
}


void _quick_sort(int *array, int low, int high)
{
	if (low < high) {
		int pivot_location = partition(array, low, high);
		_quick_sort(array, low, pivot_location - 1);
		_quick_sort(array, pivot_location + 1, high);
	}
}


/* Função auxiliar do `_quick_sort_wh_swap`. */
int partion_wh_swap(int *array, int low, int high)
{
	int i, pivot = array[high];
	int left_wall = low;

	for (i = low; i < high; ++i)

		if (array[i] < pivot) {
			_swap(&array[i], &array[left_wall]);
			++left_wall;
		}

	_swap(&array[i], &array[left_wall]);

	return left_wall;
}


void _quick_sort_wh_swap(int *array, int low, int high)
{
	if (low < high) {
		int pivot_location = partion_wh_swap(array, low, high);
		_quick_sort_wh_swap(array, low, pivot_location - 1);
		_quick_sort_wh_swap(array, pivot_location + 1, high);
	}
}


/* O mesmo que `quick_sort`, mas usando o método `swap` para trocar ítens. */
void quick_sort_wh_swap(int *array, unsigned int size)
{
	// Essa é a função de inicialização do algoritmo, a sua implementação está no método, de
	// mesmo nome, abaixo.
	void _quick_sort_wh_swap(int *array, int low, int high);
	_quick_sort_wh_swap(array, (int)0, (int)(size - 1));
}


/* Função auxiliar para fazer a troca de ítens. */
void _swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}


void print_duration(clock_t start, clock_t end)
{
	unsigned long int dif = (end - start);
	unsigned long int duration = dif * 1000 / CLOCKS_PER_SEC; // Regularização do clock.

	printf("Executado em %lu ms.\n", duration);
	// printf("Diferença de %lu clocks\n", dif);
}
