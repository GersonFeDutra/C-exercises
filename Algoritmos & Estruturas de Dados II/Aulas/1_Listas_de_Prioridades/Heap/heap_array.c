#include "heap_array.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define CHECK_HEAP(HEAP, I)                                                                        \
	if (HEAP == NULL)                                                                              \
		return NULL_ERROR;                                                                         \
	if (I > HEAP->current_size)                                                                    \
		return INVALID_INDEX_ERROR;

#define CHECK_HEAP_EMPTY(HEAP)                                                                     \
	if (HEAP == NULL)                                                                              \
		return NULL_ERROR;                                                                         \
	if (HEAP->current_size == 0)                                                                   \
		return NOT_OK;

#define MALLOC_ERROR(POINTER)                                                                      \
	if (POINTER == NULL)                                                                           \
		exit(1);

// Swap elements in an array.
#define SWAP(ARR, FROM, WITH, TYPE)                                                                \
	TYPE swap = ARR[FROM];                                                                         \
	ARR[FROM] = ARR[WITH];                                                                         \
	ARR[WITH] = swap;

#define POP(OUT, HEAP)                                                                             \
	OUT = HEAP->elements[0]->data;                                                                 \
	free(HEAP->elements[0]);                                                                       \
	_override_first(HEAP);

struct element {
	uint32_t key;
	struct data data;
};

typedef struct element *Element;

struct heap {
	uint8_t max_size;
	uint8_t current_size;
	Element *elements;
};


/* Funções auxiliares. */

/* Move um elemento na lista por elevação nas prioridades de suas chaves. */
static void _move_up(Element *elements, uint8_t i)
{
	uint8_t j = (i + 1) / 2; // Note que, nesse caso, a divisão inteira retorna o piso da operação.

	if (j == 0)
		return;

	j--;

	if (elements[i]->key > elements[j]->key) {
		SWAP(elements, i, j, Element);
		_move_up(elements, j);
	}
}


/* Move um elemento na lista por baixa nas prioridades de suas chaves. */
// static void _move_down(Element *elements, uint8_t i, uint8_t n)
// {
// 	uint8_t k = (i + 1) * 2, m = n + 1;
// 	uint8_t j = k - 1;
// 
// 	if (k > m)
// 		return;
// 
// 	if (k < m && elements[j + 1]->key > elements[j]->key)
// 		j++;
// 
// 	if (elements[i]->key < elements[j]->key) {
// 		SWAP(elements, i, j, Element)
// 		_move_down(elements, j, n);
// 	}
// }


/* Move um elemento na lista por baixa nas prioridades de suas chaves - de forma não-recursiva. */
static void _move_down(Element *elements, uint8_t i, uint8_t n)
{
	uint8_t k = (i + 1) * 2, m = n + 1;

	while (k <= m) {
		uint8_t j = k - 1;

		if (k < m && elements[j + 1]->key > elements[j]->key)
			j++;

		if (elements[i]->key < elements[j]->key) {
			SWAP(elements, i, j, Element)
			i = j;
			k = (i + 1) * 2;
		}
		else {
			break;
		}
	}
}


static void _override_first(Heap *heap)
{
	uint8_t n = heap->current_size - 1;

	heap->elements[0] = heap->elements[n];
	heap->elements[n] = NULL;
	heap->current_size--;

	if (heap->current_size != 0)
		_move_down(heap->elements, 0, heap->current_size - 1);
}


/* Funções principais. */

Heap *new_heap(uint8_t max_size)
{
	Heap *new = (Heap *)malloc(sizeof(Heap));

	if (new != NULL) {
		new->elements = (Element *)calloc(sizeof(Element), max_size);

		if (new->elements == NULL)
			free(new);
		else {
			new->max_size = max_size;
			new->current_size = 0;
		}
	}

	return new;
}


void free_heap(Heap *heap)
{
	uint8_t i;

	for (i = 0; i < heap->current_size; ++i)
		free(heap->elements[i]);

	free(heap->elements);
	free(heap);
}


// Heap *new_heap_from(struct data data[], uint32_t priorities[], uint8_t size, uint8_t max_size)
// {
// 	/* Algoritmo nº2. */
// 	Heap *new = new_heap(max_size);
//
// 	if (new != NULL && size > 0) {
// 		uint8_t i, to = size < max_size ? size : max_size;
//
// 		Element current = (Element)malloc(sizeof(struct element));
// 		MALLOC_ERROR(current)
// 		new->elements[0] = current;
// 		current->data = data[0];
// 		current->key = priorities[0];
//
// 		for (i = 1; i < to; ++i) {
// 			current = (Element)malloc(sizeof(struct element));
// 			new->elements[i] = current;
// 			current->data = data[i];
// 			current->key = priorities[i];
// 			_move_up(new->elements, i);
// 		}
// 		new->current_size = size;
// 	}
//
// 	return new;
// }


Heap *new_heap_from(struct data data[], uint32_t priorities[], uint8_t size, uint8_t max_size)
{
	/* Algoritmo nº3: Arranjar. */
	Heap *new = new_heap(max_size);
	uint8_t i, to = size < max_size ? size : max_size;

	if (new != NULL && size > 0) {
		uint8_t n = to - 1;

		for (i = 0; i < to; ++i) {
			Element current = (Element)malloc(sizeof(struct element));
			MALLOC_ERROR(current)
			new->elements[i] = current;
			current->data = data[i];
			current->key = priorities[i];
		}
		new->current_size = size;

		for (i = to / 2; i > 0; --i)
			_move_down(new->elements, i - 1, n);
	}

	return new;
}


uint8_t heap_change_priority(Heap *heap, uint8_t i, uint32_t to)
{
	CHECK_HEAP(heap, i)
	uint32_t old_priority = heap->elements[i]->key;
	heap->elements[i]->key = to;

	if (to > old_priority)
		_move_up(heap->elements, i);
	else
		_move_down(heap->elements, i, heap->current_size - 1);

	return OK;
}


uint8_t heap_insert(Heap *heap, struct data data, uint32_t priority)
{
	if (heap == NULL)
		return NULL_ERROR;

	if (heap->current_size == heap->max_size)
		return NOT_OK;

	Element new = (Element)malloc(sizeof(struct element));

	if (new == NULL)
		return NOT_OK;

	heap->elements[heap->current_size] = new;
	new->data = data;
	new->key = priority;
	_move_up(heap->elements, heap->current_size);
	heap->current_size++;

	return OK;
}


uint8_t heap_remove(Heap *heap)
{
	CHECK_HEAP_EMPTY(heap)
	free(heap->elements[0]);
	_override_first(heap);

	return OK;
}


uint8_t heap_pop(Heap *heap, struct data *out)
{
	CHECK_HEAP_EMPTY(heap)
	POP(*out, heap)

	return OK;
}


uint8_t heap_get(Heap *heap, struct data *out)
{
	if (heap == NULL)
		return NULL_ERROR;

	*out = heap->elements[0]->data;

	return OK;
}


uint8_t heap_sort(Heap *heap, struct data *(out[]))
{
	if (heap == NULL)
		return NULL_ERROR;

	uint8_t n = heap->current_size - 1;

	while (n != 0) {
		POP(*(out[n]), heap)
		// SWAP(heap->elements, 0, n, Element)
		n--;
		// _move_down(heap->elements, 0, n);
	}
}


void print_heap(Heap *heap)
{
	if (heap == NULL)
		return;

	uint8_t i;
	printf("| n° |");

	for (i = 1; i <= heap->current_size; ++i)
		printf(" %2d |", i);

	printf("\n| p  | %2d |", heap->elements[0]->key);

	for (i = 1; i < heap->current_size; ++i)
		printf(" %2u |", heap->elements[i]->key);

	printf("\n\n");
}
 