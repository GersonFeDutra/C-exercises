#include "binary_tree.h"
#include "stdint.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>


int main()
{
	setlocale(LC_ALL, "Portuguese");

	const uint8_t LEN = 10;
	struct student students[LEN];
	uint8_t i;

	for (i = 0; i < LEN; ++i)
		students[i].id = rand() % 99;

	Tree *bt = new_tree();

	if (bt == NULL)
		return 1;

	printf("Inserindo os nós:");

	for (i = 0; i < LEN; ++i) {
		printf(" %d", students[i].id);
		insert_node(bt, students[i]);
	}
	printf("\n");

	printf("Pré-ordem: ");
	travel_tree(bt, -1);
	printf("\n");

	printf("Em-ordem: ");
	travel_tree(bt, 0);
	printf("\n");

	printf("Pós-ordem: ");
	travel_tree(bt, 1);
	printf("\n");

	printf("Por profundidade: ");
	print_tree_by_level(bt);
	printf("\n");

	return 0;
}
