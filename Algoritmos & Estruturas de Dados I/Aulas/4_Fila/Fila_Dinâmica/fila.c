#include "fila.h"
#include <stdlib.h>

#define VERIFICAR_FILA(FILA)                                                                       \
	if (FILA == NULL)                                                                              \
		return NULL_ERROR;                                                                         \
	if (FILA->inicio == NULL)                                                                      \
		return EMPTY_ERROR;

// Nó descritor.
struct fila {
	struct elemento *inicio;
	struct elemento *fim;
	/* Dentro do nó descritor podemos ter qualquer informação sobre o nosso TAD, além das
	informações essenciais dessa estrutura (que nesse caso são `inicio` e `fim`): */
	// Embora `tamanho` não seja uma informação essencial pode ser útil fora do TAD.
	int tamanho; // A quantidade de elementos da fila.
	/* A desvantagem desses dados adicionais é que eles devem ser constantemente sincronizados
	conforme os dados do TAD vão sendo modificados. */
};

// Elemento individual.
struct elemento {
	struct aluno dados;
	struct elemento *proximo;
} typedef Elemento;


Fila *criar()
{
	Fila *fila;
	fila = NULL;
	fila = (Fila *)malloc(sizeof(Fila));

	if (fila != NULL) {
		fila->tamanho = 0;
		fila->inicio = NULL;
		fila->fim = NULL;
	}

	return fila;
}


int inserir(Fila *fila, struct aluno aluno)
{
	if (fila == NULL)
		return NULL_ERROR;

	Elemento *novo = (Elemento *)malloc(sizeof(Elemento));

	if (novo == NULL)
		return NOT_OK;

	novo->dados = aluno;
	novo->proximo = NULL;

	if ((fila->inicio) == NULL)
		// Não tem ninguém
		fila->inicio = novo;
	else
		// Tem alguém na fila
		fila->fim->proximo = novo;

	fila->fim = novo;
	fila->tamanho++;

	return OK;
}


int remover(Fila *fila)
{
	VERIFICAR_FILA(fila)
	Elemento *aux = fila->inicio;
	fila->inicio = fila->inicio->proximo;

	// if (fila->tamanho == 1) // O mesmo que a verificação abaixo:
	if (fila->inicio == NULL)
		// Só tinha um.
		fila->fim = NULL;

	free(aux);
	fila->tamanho--;

	return OK;
}


int acessar(Fila *fila, struct aluno *aluno)
{
	VERIFICAR_FILA(fila)
	*aluno = fila->inicio->dados;

	return OK;
}


int tamanho(Fila *fila)
{
	if (fila == NULL)
		return NULL_ERROR;

	return fila->tamanho;
}


void destruir(Fila *fila)
{
	if (fila == NULL)
		return;

	Elemento *aux;

	while (fila->inicio != NULL) {
		aux = fila->inicio;
		fila->inicio = fila->inicio->proximo;
		free(aux);
	}

	fila->fim = NULL;
	// free(fila); // Opcional: limpa o nó descritor da memória por completo.
	fila->tamanho = 0;
}
