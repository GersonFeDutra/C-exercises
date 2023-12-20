#include "locales.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>

//#define MALLOC_ERROR {WARNING("Memória insuficiente!"); return NOT_OK;}

#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__))
#define print_err(MESSAGE) fprintf(stderr, "\033[31m%s\033[m", MESSAGE)
#else
#define print_err(MESSAGE) fprintf(stderr, "%s", MESSAGE)
#endif

#define MALLOC_ERROR {                                                                                              \
		print_err(no_memory_error_message);                                                           \
		return NOT_OK;                                                                             \
	}
#define VERIFICAR_LISTA(LIST)                                                                      \
	if (LIST == NULL) {                                                                            \
		return NULL_ERROR;                                                                         \
	}                                                                                              \
	if (*LIST == NULL) {                                                                           \
		return EMPTY_ERROR;                                                                        \
	}

/* Um elemento único da lista. */
struct element {
	struct element *previous;
	struct student data;
	struct element *next;
};

/* Representação do `struct elemento` (um elemento único da lista). */
typedef struct element Element;

/* Nota: `List *` representa as seguintes opções:
- struct element **
- Element **
*/

List *list_create()
{
	List *list;
	list = (List *)malloc(sizeof(List));

	if (list == NULL) {
		print_err(no_memory_error_message);
		return NULL;
	}

	*list = NULL;

	return list;
}


int list_insert_first(List *list, struct student new_student)
{
	if (list == NULL)
		return NULL_ERROR;

	Element *new = (Element *)malloc(sizeof(Element));

	if (new == NULL)
		MALLOC_ERROR

	new->previous = NULL;
	new->data = new_student;
	new->next = *list;

	if (*list != NULL)
		(*list)->previous = new;

	*list = new;

	return OK;
}


int list_remove_first(List *list)
{
	VERIFICAR_LISTA(list)
	Element *aux = *list;
	*list = aux->next;

	if (aux->next != NULL)
		aux->next->previous = NULL;

	free(aux);

	return OK;
}


int list_access_registry(List *list, int registry, struct student *out)
{
	VERIFICAR_LISTA(list)
	Element *aux = *list;

	while (aux != NULL && aux->data.registry != registry)
		aux = aux->next;

	if (aux == NULL)
		return NOT_OK;

	*out = aux->data;

	return OK;
}


int list_access_at_index(List *list, int index, struct student *out)
{
	VERIFICAR_LISTA(list);

	Element *aux = *list;

	if (index < 0) {
		while (aux->next != NULL)
			aux = aux->next;

		for (; aux->previous != NULL && index != -1; ++index)
			aux = aux->previous;

		if (index != -1)
			return INPUT_ERROR;
	}
	else {
		for (; aux != NULL && index > 0; --index)
			aux = aux->next;

		if (aux == NULL)
			return NOT_OK;
	}
	*out = aux->data;

	return OK;
}


void list_free(List *list)
{
	if (list == NULL)
		return;

	Element *aux;

	while (*list != NULL) {
		aux = *list;
		*list = (*list)->next;
		free(aux);
	}
	// free(list); // Opcional: limpa também o ponteiro inicial, não só os elementos.
}


int list_size(List *list)
{
	if (list == NULL)
		return NULL_ERROR;

	if (*list == NULL)
		return 0;

	int valor = 0;
	Element *aux = *list;

	while (aux != NULL) {
		aux = aux->next;
		valor++;
	}

	return valor;
}


int list_insert_end(List *list, struct student new_student)
{
	if (list == NULL)
		return NULL_ERROR;

	Element *new = (Element *)malloc(sizeof(Element));

	if (new == NULL)
		MALLOC_ERROR

	new->data = new_student;
	new->next = NULL;

	if (*list == NULL) { /* lista vazia */
		(*list)->previous = NULL;
		*list = new;
	}
	else {
		Element *aux = *list;

		while (aux->next != NULL)
			aux = aux->next;

		aux->next = new;
		new->previous = aux;
	}

	return OK;
}


int list_insert_at(List *list, struct student new_student, int index)
{
	if (list == NULL)
		return NULL_ERROR;

	if (index == 0) {
		Element *new = (Element *)malloc(sizeof(Element));

		if (new == NULL)
			MALLOC_ERROR;

		new->next = *list;
		new->data = new_student;
		*list = new;

		return OK;
	}

	if (*list == NULL)
		return NOT_OK;

	Element *previous = *list;
	/* Para igualar a verificação com o 'próximo do anterior' fazemos a contagem
	 * até i(0) + 1. No caso negativo, o último elemento equivale a -1 */

	if (index < 0) { /* índice negativo */
		/* Como a lista não é circular (não há referência ao último elemento no
		 * primeiro da lista) devemos primeiro percorrer a lista até o fim */
		while (previous->next != NULL)
			previous = previous->next;

		for (; previous->previous != NULL && index != -1; ++index)
			previous = previous->previous;

		if (index != -1)
			return INPUT_ERROR;
	}
	else { /* índice positivo */
		/* Usamos o 'próximo do anterior' pois, como devemos inserir um elemento
		 * na posição do índice, isso evita armazenar um auxiliar adicional. */
		for (; previous->next != NULL && index != 1; --index)
			previous = previous->next;

		if (previous->next == NULL)
			return INPUT_ERROR;
	}

	Element *new = (Element *)malloc(sizeof(Element));

	if (new == NULL)
		MALLOC_ERROR

	new->next = previous->next;
	new->previous = previous;
	new->data = new_student;
	previous->next = new;

	return OK;
}


/* Função extra que insere com busca.
int inserir_apos(List *list, struct student new, int registry)
{
    VERIFICAR_LISTA(list)

    Element *current = *list;

    while (current != NULL && current->data.registry != registry)
        current = current->next;

    if (current == NULL)
        return NOT_OK;

    Element *next = current->next;
    Element *new = (Element *)malloc(sizeof(Element));

    if (new == NULL) MALLOC_ERROR

    new->data = new;
    new->next = current->next;
    free(next);

    return OK;
}
*/


int list_remove_end(List *list)
{
	VERIFICAR_LISTA(list)

	if ((*list)->next == NULL) { /* Lista só tem um elemento */
		free(*list);
		*list = NULL;
	}
	else {
		Element *current = (*list)->next; /* Começa verificando o segundo */

		while (current->next != NULL)
			current = current->next;

		current->previous->next = NULL;
		free(current);
	}

	return OK;
}


int list_remove_at(List *list, int index)
{
	VERIFICAR_LISTA(list)


	if (index == 0) {
		Element *aux = (*list)->next;

		if (aux != NULL)
			aux->previous = NULL;

		free(*list);
		*list = aux;

		return OK;
	}

	Element *previous = *list;

	if (index < 0) { /* índice negativo */
		/* Como a lista não é circular (não há referência ao último elemento no
		 * primeiro da lista) devemos primeiro percorrer a lista até o fim */
		while (previous->next != NULL)
			previous = previous->next;

		for (; previous->previous != NULL && index != -1; ++index)
			previous = previous->previous;

		if (index != -1)
			return INPUT_ERROR;
	}
	else {
		// Para igualar a verificação com o 'próximo do anterior' iniciamos a contagem pelo i(0) + 1.
		/* Usamos o 'próximo do anterior' pois, como devemos inserir um elemento na posição do índice,
		isso evita armazenar um auxiliar adicional. */
		for (; previous->next != NULL && index != 1; --index)
			previous = previous->next;

		if (previous->next == NULL)
			return NOT_OK;
		
		previous->next = previous->next->next;
	}

	aux = previous->next->next;
	free(previous->next);
	previous->next = aux;

	return OK;
}


int list_remove_registry(List *list, int registry)
{
	VERIFICAR_LISTA(list)
	Element *previous = *list; // Começa como o primeiro elemento da lista.
	// Começa como o segundo elemento da lista, possivelmente NULL.
	Element *current = previous->next;

	if (current == NULL) {

		if (registry != previous->data.registry)
			return NOT_OK;

		free(previous);
		*list = NULL;
	}
	else {
		while (current->data.registry != registry && current->next != NULL) {
			previous = current;
			current = current->next;
		}

		if (current->next == NULL && current->data.registry != registry)
			return NOT_OK;

		previous->next = current->next;
		free(current);
	}

	return OK;
}


int list_is_empty(List *list)
{
	if (list == NULL)
		return NULL_ERROR;

	if (*list == NULL)
		return OK;

	return NOT_OK;
}

/* Desnecessário
int list_is_full(List *list)
{
    return NOT_OK;
}
*/
