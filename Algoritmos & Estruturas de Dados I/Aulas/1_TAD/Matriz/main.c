#include "matriz.h"
#include <stdio.h>
#include <stdlib.h>


int main()
{
	int i, j;
	Matriz *matriz = cria(3, 4);

	for (i = 0; i < linhas(matriz); i++)

		for (j = 0; j < colunas(matriz); j++)
			atribui(matriz, i, j, i * j);

	for (i = 0; i < linhas(matriz); i++) {

		for (j = 0; j < colunas(matriz); j++)
			printf("%.2f\t", acessa(matriz, i, j));

		printf("\n");
	}
	// libera(matriz);

	return 0;
}
