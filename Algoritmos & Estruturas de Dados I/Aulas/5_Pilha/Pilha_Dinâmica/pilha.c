#include "pilha.h"
#include <stdlib.h>

#define VERIFICAR_PILHA(PILHA)                                                                     \
	if (PILHA == NULL)                                                                             \
		return NULL_ERROR;                                                                         \
	if (*PILHA == NULL)                                                                            \
		return EMPTY_ERROR;

struct elemento {
	struct aluno dados;
	struct elemento *proximo;
} typedef Elemento;


Pilha *criar(void)
{
	Pilha *pilha = (Pilha *)malloc(sizeof(Pilha));

	if (pilha != NULL)
		*pilha = NULL;

	return pilha;
}


int inserir(Pilha *pilha, struct aluno novos_dados)
{
	if (pilha == NULL)
		return NULL_ERROR;

	Elemento *novo = (Elemento *)malloc(sizeof(Elemento));

	if (novo == NULL)
		return 0;

	novo->dados = novos_dados;
	novo->proximo = *pilha;
	*pilha = novo;

	return OK;
}


int remover(Pilha *pilha)
{
	VERIFICAR_PILHA(pilha)
	Elemento *aux = *pilha;
	*pilha = aux->proximo;
	free(aux);

	return OK;
}


int acessar(Pilha *pilha, struct aluno *saida)
{
	VERIFICAR_PILHA(pilha)
	*saida = (*pilha)->dados;

	return OK;
}


void destruir(Pilha *pilha)
{
	if (pilha == NULL)
		return;

	Elemento *aux;

	while (*pilha != NULL) {
		aux = *pilha;
		*pilha = aux->proximo;
		free(aux);
	}
	// free(pilha);
}


// Desnecessário: por meio da função `tamanho` já podemos identificar se a pilha está vazia.
// int vazia(Pilha *pilha)
// {
// 	if (pilha == NULL)
// 		return NULL_ERROR;

// 	return *pilha == NULL;
// }


int tamanho(Pilha *pilha)
{
	if (pilha == NULL)
		return NULL_ERROR;

	int value = 0;
	Elemento *aux = *pilha;

	while (aux != NULL) {
		aux = aux->proximo;
		++value;
	}

	return value;
}
