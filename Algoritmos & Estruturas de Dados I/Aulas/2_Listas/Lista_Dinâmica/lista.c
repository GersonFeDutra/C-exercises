#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

//#define MALLOC_ERROR {WARNING("Memória insuficiente!"); return NOT_OK;}

#define MALLOC_ERROR                                                                               \
	{                                                                                              \
		printf("Memória insuficiente!\n");                                                         \
		return NOT_OK;                                                                             \
	}
#define VERIFICAR_LISTA(LISTA)                                                                     \
	if (LISTA == NULL) {                                                                           \
		return NULL_ERROR;                                                                         \
	}                                                                                              \
	if (*LISTA == NULL) {                                                                          \
		return EMPTY_ERROR;                                                                        \
	}

/* Um elemento único da lista. */
struct elemento {
	struct aluno dados;
	struct elemento *proximo;
};

/* Representação do `struct elemento` (um elemento único da lista). */
typedef struct elemento Elemento;

/* Nota: `Lista *` representa as seguintes opções:
- struct elemento **
- Elemento **
*/

Lista *criar()
{
	Lista *lista;
	lista = (Lista *)malloc(sizeof(Lista));

	if (lista == NULL) {
		printf("Erro: Memória insuficiente!\n");
		return NULL;
	}

	*lista = NULL;

	return lista;
}


int inserir_inicio(Lista *lista, struct aluno novo_aluno)
{
	if (lista == NULL)
		return NULL_ERROR;

	Elemento *novo = (Elemento *)malloc(sizeof(Elemento));

	if (novo == NULL)
		MALLOC_ERROR

	novo->dados = novo_aluno;
	novo->proximo = *lista;
	*lista = novo;

	return OK;
}


int remover_inicio(Lista *lista)
{
	VERIFICAR_LISTA(lista)
	Elemento *aux = *lista;
	*lista = aux->proximo;
	free(aux);

	return OK;
}


int acessar_por_matricula(Lista *lista, int matricula, struct aluno *saida)
{
	VERIFICAR_LISTA(lista)
	Elemento *aux = *lista;

	while (aux != NULL && aux->dados.matricula != matricula)
		aux = aux->proximo;

	if (aux == NULL)
		return NOT_OK;

	*saida = aux->dados;

	return OK;
}


int acessar_por_indice(Lista *lista, int indice, struct aluno *saida)
{
	VERIFICAR_LISTA(lista);

	if (indice < 0)
		// WARNING("Entrada inválida: ìndice negativo!"); return NOT_OK;
		return INPUT_ERROR;

	int i = 0;
	Elemento *aux = *lista;

	while (aux != NULL && i != indice) {
		aux = aux->proximo;
		++i;
	}

	if (aux == NULL)
		return NOT_OK;

	*saida = aux->dados;

	return OK;
}


void destruir(Lista *lista)
{
	if (lista == NULL)
		return;

	Elemento *aux;

	while (*lista != NULL) {
		aux = *lista;
		*lista = (*lista)->proximo;
		free(aux);
	}
	// free(l); // Opcional: limpa também o ponteiro inicial, não só os elementos.
}


int tamanho(Lista *lista)
{
	if (lista == NULL)
		return NULL_ERROR;

	if (*lista == NULL)
		return 0;

	int valor = 0;
	Elemento *aux = *lista;

	while (aux != NULL) {
		aux = aux->proximo;
		valor++;
	}

	return valor;
}


int inserir_fim(Lista *lista, struct aluno novo_aluno)
{
	if (lista == NULL)
		return NULL_ERROR;

	Elemento *novo_elemento = (Elemento *)malloc(sizeof(Elemento));

	if (novo_elemento == NULL)
		MALLOC_ERROR

	novo_elemento->dados = novo_aluno;
	novo_elemento->proximo = NULL;

	if (*lista == NULL) {
		*lista = novo_elemento;
	}
	else {
		Elemento *aux = *lista;

		while (aux->proximo != NULL)
			aux = aux->proximo;

		aux->proximo = novo_elemento;
	}

	return OK;
}


int inserir_meio(Lista *lista, struct aluno novo_aluno, int indice)
{
	if (lista == NULL)
		return NULL_ERROR;

	if (indice < 0)
		return INPUT_ERROR;

	if (indice == 0) {
		Elemento *novo = (Elemento *)malloc(sizeof(Elemento));

		if (novo == NULL)
			MALLOC_ERROR;

		novo->proximo = *lista;
		novo->dados = novo_aluno;
		*lista = novo;

		return OK;
	}

	if (*lista == NULL)
		return NOT_OK;

	int i = 1;
	Elemento *anterior = *lista;
	// Para igualar a verificação com o 'próximo do anterior' iniciamos a contagem pelo i(0) + 1.
	/* Usamos o 'próximo do anterior' pois, como devemos inserir um elemento na posição do índice,
	isso evita armazenar um auxiliar adicional. */
	while (anterior->proximo != NULL && i != indice) {
		anterior = anterior->proximo;
		++i;
	}

	if (anterior->proximo == NULL)
		return NOT_OK;

	Elemento *novo = (Elemento *)malloc(sizeof(Elemento));

	if (novo == NULL)
		MALLOC_ERROR

	novo->proximo = anterior->proximo;
	novo->dados = novo_aluno;
	anterior->proximo = novo;

	return OK;
}


/* Função extra que insere com busca.
int inserir_apos(Lista *lista, struct aluno novo, int matricula)
{
    VERIFICAR_LISTA(lista)

    Elemento *atual = *lista;

    while (atual != NULL && atual->dados.matricula != matricula)
        atual = atual->proximo;

    if (atual == NULL)
        return NOT_OK;

    Elemento *proximo = atual->proximo;
    Elemento *novo_elemento = (Elemento *)malloc(sizeof(Elemento));

    if (novo_elemento == NULL) MALLOC_ERROR

    novo_elemento->dados = novo;
    novo_elemento->proximo = atual->proximo;
    free(proximo);

    return OK;
}
*/


int remover_fim(Lista *lista)
{
	VERIFICAR_LISTA(lista)
	Elemento *anterior = *lista; // Começa como o primeiro elemento da lista.
	// Começa como o segundo elemento da lista, possivelmente `NULL`.
	Elemento *atual = anterior->proximo;

	if (atual == NULL) {
		free(anterior);
		*lista = NULL;
	}
	else if (atual->proximo == NULL) {
		/* Fiz esse `esse if` adicional para evitar ficar dando cache em `anterior` e `atual` ao
		mesmo tempo durante a iteração do loop abaixo. */
		free(atual);
		anterior->proximo = NULL;
	}
	else {
		while (atual->proximo->proximo != NULL)
			atual = atual->proximo;

		anterior = atual;
		atual = atual->proximo;
		anterior->proximo = atual->proximo; // Equivalente à `... = NULL`.
		free(atual);
	}

	return OK;
}


int remover_meio(Lista *lista, int indice)
{
	VERIFICAR_LISTA(lista)

	if (indice < 0)
		return INPUT_ERROR;
	
	Elemento *aux;
	
	if (indice == 0) {
		aux = (*lista)->proximo;
		free(*lista);
		*lista = aux;
		
		return OK;
	}

	int i = 1;
	Elemento *anterior = *lista;
	// Para igualar a verificação com o 'próximo do anterior' iniciamos a contagem pelo i(0) + 1.
	/* Usamos o 'próximo do anterior' pois, como devemos inserir um elemento na posição do índice,
	isso evita armazenar um auxiliar adicional. */
	while (anterior->proximo != NULL && i != indice) {
		anterior = anterior->proximo;
		++i;
	}

	if (anterior->proximo == NULL)
		return NOT_OK;

	aux = anterior->proximo->proximo;
	free(anterior->proximo);
	anterior->proximo = aux;

	return OK;
}


int remover_por_matricula(Lista *lista, int matricula)
{
	VERIFICAR_LISTA(lista)
	Elemento *anterior = *lista; // Começa como o primeiro elemento da lista.
	// Começa como o segundo elemento da lista, possivelmente NULL.
	Elemento *atual = anterior->proximo;

	if (atual == NULL) {

		if (matricula != anterior->dados.matricula)
			return NOT_OK;

		free(anterior);
		*lista = NULL;
	}
	else {
		while (atual->dados.matricula != matricula && atual->proximo != NULL) {
			anterior = atual;
			atual = atual->proximo;
		}

		if (atual->proximo == NULL && atual->dados.matricula != matricula)
			return NOT_OK;

		anterior->proximo = atual->proximo;
		free(atual);
	}

	return OK;
}


int vazia(Lista *lista)
{
	if (lista == NULL)
		return NULL_ERROR;

	if (*lista == NULL)
		return OK;

	return NOT_OK;
}

/* Desnecessário
int cheia(Lista *lista)
{
    return NOT_OK;
}
*/
