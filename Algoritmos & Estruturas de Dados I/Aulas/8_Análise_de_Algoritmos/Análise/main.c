#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main()
{
	setlocale(LC_ALL, "Portuguese");

	clock_t inicio, fim;
	unsigned long int duracao;
	inicio = clock();

	// Seu algoritmo vai aqui.

	fim = clock();
	duracao = (fim - inicio) * 1000 / CLOCKS_PER_SEC; // Regularização do clock.
	printf("Executado em %lu ms.\n", duracao);

	return 0;
}
