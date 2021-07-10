#include "heap_array.h"
#include "stdint.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
	setlocale(LC_ALL, "Portuguese");

	Heap *heap;

	// 	heap = new_heap(15);
	//
	// 	// if (heap == NULL)
	// 	// 	return 1;
	//
	// 	struct data data = {.number = 10};
	// 	data.name = (char *)malloc(sizeof(char) * 15);
	// 	strcpy(data.name, "teste");
	// 	printf("%u\n", heap_insert(heap, data, 1));
	//
	// 	struct data ret;
	// 	printf("%u\n", heap_pop(heap, &ret));
	// 	printf("%d %s\n", ret.number, ret.name);

	const uint8_t LEN = 10;
	uint8_t i;
	uint32_t priorities_list[LEN];
	struct data data_list[LEN];

	for (i = 0; i < LEN; ++i) {
		data_list[i].name = (char *)malloc(sizeof(char) * 4);
		sprintf(data_list[i].name, "%d", i);
		priorities_list[i] = data_list[i].number = i + 1;
	}

	heap = new_heap_from(data_list, priorities_list, LEN, LEN);
	print_heap(heap);
	// mu
	// | p  | 10 |  9 |  6 |  7 |  8 |  2 |  5 |  1 |  4 |  3 |
	// md
	// | p  | 10 |  9 |  7 |  8 |  5 |  6 |  3 |  1 |  4 |  2 |
	// md-nr
	// | p  | 10 |  9 |  7 |  8 |  5 |  6 |  3 |  1 |  4 |  2 |

	return 0;
}
