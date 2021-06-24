#include <locale.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_array(int *arr, uint8_t n);


/* Assumindo que n > 2, retorna os dois maiores valores do vetor `arr`.
Escreva um algoritmo que execute a seguinte tarefa: Dado um vetor n ̃ao ordenado com n
elementos (n ≥ 1), encontre o maior e o segundo maior elementos deste vetor. Seu
algoritmo dever ́a percorrer o vetor uma única vez. */
void get_highers(int arr[], uint8_t n, int highers[2])
{
	uint8_t i = 1, to = n - 1;

	// if (n < 1)
	// 	return;

	// if (n < 2) {
	// 	highers[0] = highers[1] = arr[0];
	// 	return;
	// }

	while (arr[i] == arr[0] && i < to)
		++i;

	if (arr[0] > arr[i]) {
		highers[0] = arr[0];
		highers[1] = arr[i];
	}
	else {
		highers[0] = arr[i];
		highers[1] = arr[0];
	}
	++i;

	for (; i < n; ++i)

		if (arr[i] > highers[0]) {
			highers[1] = highers[0];
			highers[0] = arr[i];
		}
		else if (arr[i] == highers[0])
			continue;
		else if (arr[i] > highers[1])
			highers[1] = arr[i];
}


/* Sejam f1, f2, ..., fn uma sequência de elementos definida da seguinte forma:
f1 = 0, f2 = 1, f3 = 1 e fj = fj−1 − fj−2 + fj−3, para j > 3.
Elabore um algoritmo não recursivo que determine o valor de fn.
Calcule sua complexidade em função de n. */
uint32_t get_fn(uint8_t n)
{
	uint8_t i;
	uint32_t f1 = 0, f2 = 1, f3 = 1;

	if (n < 2)
		return f1;

	else if (n == 2)
		return f2;

	else if (n == 3)
		return f3;

	uint64_t fn;

	for (i = 3; i < n; ++i) {
		fn = f3 - f2 + f1;
		f1 = f2;
		f2 = f3;
		f3 = fn;
	}

	return fn;
}


/* Radix Sort
Dado um vetor V com n elementos, considere o seguinte algoritmo de ordenacão:
* Seja m(V) o valor do maior elemento de V.
* Crie um novo vetor auxiliar A de tamanho m(V), com todas as posições inicialmente iguais a zero.
* Para cada ocorrência de um elemento de valor x em V, acrescente em uma unidade o valor da posicão
x em A.
* Ao final do passo anterior, para cada posicão i de A, faça A[i] cópias do valor i em V, caso A[i]
seja positivo, seguindo da posiçao inicial à final. */
void radix_sort(int v[], uint8_t n, int mv)
{
	uint8_t i, j;
	int to = mv + 1;
	int a[to], x;

	for (i = 0; i < to; ++i)
		a[i] = 0;

	for (i = 0; i < n; ++i)
		a[v[i]]++;

	j = 0;
	for (i = 0; i < to; ++i) {
		uint8_t k;

		for (k = 0; k < a[i]; ++k) {
			v[j] = i;
			++j;
		}
	}
}


int main()
{
	setlocale(LC_ALL, "Portuguese");

	void do_get_highers();
	do_get_highers();
	void do_fn();
	do_fn();
	void do_radix_sort();
	do_radix_sort();

	return 0;
}


void do_get_highers()
{
	srand(time(0));
	uint8_t i, n = (rand() % 7 + 2);
	int array[n];

	for (i = 0; i < n; ++i)
		array[i] = rand() % n;

	print_array(array, n);

	int highers[2];
	get_highers(array, n, highers);
	print_array(highers, 2);
}


void do_fn()
{
	void do_fn_line(uint8_t * from);
	uint8_t i, f;

	for (i = 0; i < 2; ++i)
		do_fn_line(&f);
}


void do_fn_line(uint8_t *from)
{
	uint8_t i;

	for (i = 0; i < 16; ++i) {
		(*from)++;
		printf("<%d:%u> ", *from, get_fn(*from));
	}

	printf("\n");

	*from = i;
}


void do_radix_sort()
{
	const uint8_t SIZE = 10;
	int v[] = {5, 9, 13, 4, 35, 12, 0, 36, 5, 45};
	int mv = 36;
	print_array(v, SIZE);
	radix_sort(v, SIZE, mv);
	print_array(v, SIZE);
}


void print_array(int *arr, uint8_t n)
{
	uint8_t i, to = n - 1;
	printf("[");

	for (i = 0; i < to; ++i)
		printf("%d, ", arr[i]);

	printf("%d]\n", arr[to]);
}
