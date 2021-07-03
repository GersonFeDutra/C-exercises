#include "fila.h"
#include <stdlib.h>

#define CHECAR_FILA(FILA)                                                                          \
	if (FILA == NULL)                                                                              \
		return NULL_ERROR;                                                                         \
	if (FILA->quantidade == 0)                                                                     \
		return EMPTY_ERROR;

// Nó descritor.
struct fila {
	int quantidade;
	int inicio;
	int fim;
	struct aluno dados[MAX];
};


Fila *criar()
{
	Fila *fila;
	fila = NULL;
	fila = (Fila *)malloc(sizeof(Fila));

	if (fila != NULL) {
		fila->quantidade = 0;
		fila->inicio = 0;
		fila->fim = 0;
	}

	return fila;
}


int inserir(Fila *fila, struct aluno aluno)
{
	if (fila == NULL)
		return NULL_ERROR;

	if (fila->quantidade == MAX)
		return NOT_OK;

	fila->dados[fila->fim] = aluno;
	fila->quantidade++;
	fila->fim = (fila->fim + 1) % MAX;

	return OK;
}


int remover(Fila *fila)
{
	CHECAR_FILA(fila)
	fila->inicio = (fila->inicio + 1) % MAX;
	fila->quantidade--;

	return OK;
}


int acessar(Fila *fila, struct aluno *aluno)
{
	CHECAR_FILA(fila)
	*aluno = fila->dados[fila->inicio];

	return OK;
}


int tamanho(Fila *fila)
{
	if (fila == NULL)
		return NULL_ERROR;

	return fila->quantidade;
}


void destruir(Fila *fila)
{
	if (fila == NULL)
		return;

	// Esse método pode ser implementado de ambas as formas...
	// Apenas "esvazia" o conteúdo.
	fila->quantidade = 0;
	fila->inicio = 0;
	fila->fim = 0;
	// ou:
	// free(fila); // Remove o endereço de memória do TAD.
}
