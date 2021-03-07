#include "integer_set.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE "-----------------------------------------------------------\n"
#define SHORT_LINE "----------------------"

void print_set_l(char set_name[], IntSet *set);
void print_merge(IntSet *set_a, IntSet *set_b, char set_a_name[], char set_b_name[]);
void print_complementary(
	IntSet *minor_set, IntSet *major_set, char minor_set_name[], char major_set_name[]);


int main()
{
	setlocale(LC_ALL, "Portuguese");

	void testes(void);
	testes();

	IntSet *set_a = new_set(), *set_b = new_set(), *set_c = new_set();

	printf(
		"Preencha 3 conjuntos de inteiros para ver o resultado de algumas operações entre eles:\n");
	printf(LINE);
	fill_in(set_a);
	print_set_l("A", set_a);
	printf(LINE);
	fill_in(set_b);
	print_set_l("B", set_b);
	printf(LINE);
	fill_in(set_c);
	print_set_l("C", set_c);

	// União
	printf(SHORT_LINE "---- União ----" SHORT_LINE "\n");
	print_merge(set_a, set_b, "A", "B");
	print_merge(set_b, set_c, "B", "C");
	print_merge(set_a, set_c, "A", "C");
	print_merge(set_a, set_a, "A", "A");
	print_merge(set_b, set_b, "B", "B");

	// Intersecção
	printf(SHORT_LINE "- Intersecção -" SHORT_LINE "\n");
	print_set_l("A ∩ B", intersection(set_a, set_b));
	print_set_l("B ∩ C", intersection(set_b, set_c));
	print_set_l("A ∩ C", intersection(set_a, set_c));
	print_set_l("A ∩ A", intersection(set_a, set_a));
	print_set_l("B ∩ B", intersection(set_b, set_b));

	// Diferença
	printf(SHORT_LINE "-- Diferença --" SHORT_LINE "\n");
	print_set_l("A - B", diff(set_a, set_b));
	print_set_l("B - A", diff(set_b, set_a));
	print_set_l("B - C", diff(set_b, set_c));
	print_set_l("C - B", diff(set_c, set_b));
	print_set_l("A - C", diff(set_a, set_c));
	print_set_l("C - A", diff(set_c, set_a));
	print_set_l("A - A", diff(set_a, set_a));
	print_set_l("B - B", diff(set_b, set_b));

	// A contido em B
	printf(SHORT_LINE " A contido em B " SHORT_LINE "\n");
	printf("A %s B\n", is_contained(set_a, set_b) ? "⊂" : "⊄");
	printf("B %s A\n", is_contained(set_b, set_a) ? "⊂" : "⊄");
	printf("B %s C\n", is_contained(set_b, set_c) ? "⊂" : "⊄");
	printf("C %s B\n", is_contained(set_c, set_b) ? "⊂" : "⊄");
	printf("A %s C\n", is_contained(set_a, set_c) ? "⊂" : "⊄");
	printf("C %s B\n", is_contained(set_c, set_a) ? "⊂" : "⊄");
	printf("A %s A\n", is_contained(set_a, set_a) ? "⊆" : "⊄");

	// Conjunto complementar de A em B
	printf(SHORT_LINE "- Complementar -" SHORT_LINE "\n");
	print_complementary(set_a, set_b, "A", "B");
	print_complementary(set_b, set_a, "B", "A");
	print_complementary(set_b, set_c, "B", "C");
	print_complementary(set_c, set_b, "C", "B");
	print_complementary(set_a, set_c, "A", "C");
	print_complementary(set_c, set_a, "C", "A");

	return 0;
}


/* Alguns testes 'automáticos'. */
void testes()
{
	// IntSet *set = new_set();
	// //int test_a[14] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
	// //printf("%d\n", fill(set, test, 14));
	// int test_b[8] = {1, 2, 3, 4, 5, 6, 7, 8};
	// printf("%d\n", fill(set, test_b, 8));
	// //printf("%d\n", fill(set, test_b, -8));

	IntSet *set_a = new_set();
	IntSet *set_b = new_set();
	int test_c[4] = {1, 2, 3, 4};
	int test_d[5] = {1, 2, 3, 4, 5};

	// Conjuntos vazios
	// print_set_l("A", set_a);
	// print_set_l("B", set_b);
	// print_merge(set_a, set_b, "A", "B");

	// Preenchimento
	if (!fill(set_a, test_c, 4))
		printf("Erro ao preencher conjunto A!\n");
	print_set_l("A", set_a);
	if (!fill(set_b, test_d, 5))
		printf("Erro ao preencher conjunto B!\n");
	print_set_l("B", set_b);

	// União
	print_merge(set_a, set_b, "A", "B");
	print_merge(set_a, set_a, "A", "A");
	print_merge(set_b, set_b, "B", "B");

	int test_e[6] = {-1, -2, -3, -4, -5, -6};
	IntSet *set_c = new_set();

	if (!fill(set_c, test_e, 6))
		printf("Erro ao preencher conjunto C!\n");
	print_set_l("C", set_c);
	print_merge(set_b, set_c, "B", "C");

	// Intersecção
	print_set_l("A ∩ B", intersection(set_a, set_b));
	print_set_l("A ∩ A", intersection(set_a, set_a));
	print_set_l("B ∩ B", intersection(set_b, set_b));
	print_set_l("B ∩ C", intersection(set_c, set_b));
	// print_set_l("A ∩ ∅", intersection(set_a, new_set()));
	// print_set_l("∅ ∩ ∅", intersection(new_set(), new_set()));

	// Diferença
	print_set_l("A - B", diff(set_a, set_b));
	print_set_l("B - A", diff(set_b, set_a));
	print_set_l("A - A", diff(set_a, set_a));
	print_set_l("B - B", diff(set_b, set_b));
	print_set_l("B - C", diff(set_b, set_c));
	print_set_l("C - B", diff(set_c, set_b));
	// print_set_l("A - ∅", diff(set_a, new_set()));
	// print_set_l("∅ - ∅", diff(new_set(), new_set()));

	// A contido em B
	printf("A %s B\n", is_contained(set_a, set_b) ? "⊂" : "⊄"); // opcionalmente usar ⊆
	printf("B %s A\n", is_contained(set_b, set_a) ? "⊂" : "⊄");
	printf("A %s A\n", is_contained(set_a, set_a) ? "⊆" : "⊄");
	printf("B %s C\n", is_contained(set_b, set_c) ? "⊂" : "⊄");
	printf("C %s B\n", is_contained(set_c, set_b) ? "⊂" : "⊄");
	printf("C %s ∅\n", is_contained(set_c, new_set()) ? "⊂" : "⊄");
	printf("∅ %s C\n", is_contained(new_set(), set_c) ? "⊂" : "⊄");

	// Conjunto complementar de A em B.
	print_complementary(set_a, set_b, "A", "B");
	print_complementary(set_b, set_a, "B", "A");
	// print_complementary(set_c, set_b, "C", "B");
	print_complementary(new_set(), set_c, "∅", "C");
	// print_complementary(set_c, new_set(), "C", "∅");

	printf("\n");
}


// Funções de apoio
/* Imprime o conjunto em uma linha. */
void print_set_l(char set_name[], IntSet *set)
{
	printf("%s = ", set_name);
	print_set(set);
	printf("\n");
}


/* Faz a união do conjuntos e imprime o resultado */
void print_merge(IntSet *set_a, IntSet *set_b, char set_a_name[], char set_b_name[])
{
	IntSet *set_ab = new_set();

	if (!merge(set_a, set_b, set_ab)) {
		printf("Erro ao unir conjuntos: %s U %s. O tamanho do conjunto união é >%d.\n", set_a_name,
			set_b_name, MAX_SIZE);
		return;
	}

	printf("%s U %s", set_a_name, set_b_name);
	print_set_l("\0", set_ab);
}


void print_complementary(
	IntSet *minor_set, IntSet *major_set, char minor_set_name[], char major_set_name[])
{
	IntSet *set = new_set();

	if (complementary(minor_set, major_set, set)) {
		printf("O conjunto complementar de %s em relação à %s:", minor_set_name, major_set_name);
		print_set_l("\0", set);
	}
	else {
		printf("O conjunto %s não possui complementar em relação à %s, pois %s ⊄ %s.\n",
			minor_set_name, major_set_name, minor_set_name, major_set_name);
	}
}
