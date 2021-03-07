#include "matriz.h"
#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1
#define ALLOC_FAIL                                                                                                     \
	{                                                                                                                  \
		printf("Memória insuficiente!");                                                                               \
		exit(1);                                                                                                       \
	}

struct matriz {
	int linhas;
	int colunas;
	float **valores;
};


Matriz *cria(int linhas, int colunas)
{
	int i, j;
	Matriz *matriz = (Matriz *)malloc(sizeof(Matriz));

	if (matriz == NULL)
		ALLOC_FAIL

	matriz->linhas = linhas;
	matriz->colunas = colunas;
	matriz->valores = (float **)malloc(linhas * sizeof(float *));

	if (matriz->valores == NULL)
		ALLOC_FAIL

	for (i = 0; i < linhas; i++) {
		matriz->valores[i] = (float *)malloc(colunas * sizeof(float));

		if (matriz->valores[i] == NULL)
			ALLOC_FAIL

		for (j = 0; j < colunas; j++)
			matriz->valores[i][j] = 0.0;
	}

	return matriz;
}


void libera(Matriz *matriz)
{
	int i;

	if (matriz == NULL) {
		printf("Matriz inexistente");
		return;
	}

	for (i = 0; i < matriz->linhas; i++)
		free(matriz->valores[i]);

	free(matriz->valores);
	free(matriz);
}


float acessa(Matriz *matriz, int linha, int coluna)
{
	int _verificar_matriz(Matriz *, int linha, int coluna);

	if (!_verificar_matriz(matriz, linha, coluna))
		exit(1);

	return matriz->valores[linha][coluna];
}


void atribui(Matriz *matriz, int linha, int coluna, float valor)
{
	int _verificar_matriz(Matriz *, int linha, int coluna);

	if (!_verificar_matriz(matriz, linha, coluna))
		exit(1);

	matriz->valores[linha][coluna] = valor;
}


int linhas(Matriz *matriz)
{
	if (matriz == NULL) {
		printf("Matriz não existe!");
		exit(1);
	}
	else {
		return matriz->linhas;
	}
}


int colunas(Matriz *matriz)
{
	if (matriz == NULL) {
		printf("Matriz não existe!");
		exit(1);
	}
	else {
		return matriz->colunas;
	}
}


int _verificar_matriz(Matriz *matriz, int linha, int coluna)
{
	if (matriz == NULL) {
		printf("Matriz não existe!");
		return FALSE;
	}

	if (linha < 0 || linha >= matriz->linhas) {
		printf("Linha fora da matriz!");
		return FALSE;
	}

	if (coluna < 0 || coluna >= matriz->colunas) {
		printf("Matriz não existe!");
		return FALSE;
	}

	return TRUE;
}
