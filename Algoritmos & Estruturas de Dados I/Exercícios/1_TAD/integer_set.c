#include "integer_set.h"
#include "input_validate.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Aparentemente warnings e errors são específicas por compilador. Pra evitar conflitos removi as
seções de código que usam pragma. */
// #ifndef DEBUG
// 	#define WARNING(statement) _Pragma ("GCC warning \"Must be fixed for release version.\"")
// 	#define ERROR(statement) _Pragma ("GCC error \"Must be fixed for release version.\"")
// 	// ("GCC error \"Must be fixed for release version\"")
// #else
// 	#define WARNING(statement) statement
// 	#define ERROR(statement) statement
// #endif

const char ORDINARY[][10] = {"primeiro", "segundo", "terceiro", "quarto", "quinto", "sexto",
	"sétimo", "oitavo", "nono", "décimo"};

struct integer_set {
	int size;
	int elementos[MAX_SIZE];
};


IntSet *new_set()
{
	int i;
	IntSet *set = (IntSet *)malloc(sizeof(IntSet));
	set->size = 0;

	return set;
}


void fill_in(IntSet *set)
{
	int i = 0, size;
	int _is_on_set(int value, IntSet *set);
	char invalid_message[] = "Entrada inválida, por favor, tente novamente";
	char empty_input_message[] = "Entrada vazia, por favor, insira um valor válido";
	char size_message[45 + INT_MAX_DIGITS] = {'\0'};
	char out_of_range_message[60 + INT_MAX_DIGITS];
	sprintf(size_message, "Quantos elementos deseja inserir? (0 - %d)", MAX_SIZE);
	sprintf(out_of_range_message, "O valor deve estar entre 0 e %d. Por favor, tente novamente",
		MAX_SIZE);

	size = input_integer_range(
		0, MAX_SIZE, size_message, invalid_message, empty_input_message, out_of_range_message);
	// if (input_boolean_choice("Deseja manter o conjunto vazio?", "Ss", "Nn",
	// 		invalid_message, empty_input_message))
	// 	return;

	// do {
	for (i = 0; i < size; ++i) {
		char message[96] = "Digite o ";
		int value = input_integer(
			strcat(strcat(message, ORDINARY[i]), " número"), invalid_message, empty_input_message);

		while (_is_on_set(value, set)) {
			char snum[INT_MAX_DIGITS];

			strcpy(message, "O valor digitado '");
			sprintf(snum, "%d", value);
			value = input_integer(
				strcat(strcat(message, snum), "' já está no conjunto. Por favor, tente novamente"),
				invalid_message, empty_input_message);
		}

		(set->size)++;
		set->elementos[i] = value;
		//++i;

		if (i == MAX_SIZE)
			break;
	}
	// } while (
	// 	input_boolean_choice("Deseja continuar?", "Ss", "Nn", invalid_message, empty_input_message)
	// );
}


int fill(IntSet *set, int *arr, int size)
{
	int _is_on_set(int value, IntSet *set);
	int i;

	if (size <= 0) {
		// WARNING("Aviso! O vetor passada deve ter tamanho >= 0.");
		printf("Aviso! O vetor passada deve ter tamanho >= 0.\n");
		return FALSE;
	}

	if (size > MAX_SIZE) {
		// WARNING("Aviso! O vetor passada deve ter tamanho <= MAX_SIZE. Demais valores serão
		// ignorados.");
		printf("Aviso! O vetor passada deve ter tamanho <= %d. Demais valores serão ignorados.\n",
			MAX_SIZE);
		size = MAX_SIZE;
	}

	for (i = 0; i < size; ++i) {

		if (_is_on_set(arr[i], set)) {
			// WARNING("Aviso! O conjunto não pode ter elementos repetidos!");
			printf("Aviso! O conjunto não pode ter elementos repetidos.\n");
			return FALSE;
		}
		set->elementos[i] = arr[i];
		(set->size)++;
	}
	return TRUE;
}


int merge(IntSet *set_a, IntSet *set_b, IntSet *set_out)
{
	int _is_on_set(int value, IntSet *set);
	int i, out_i = set_a->size;

	set_out->size = 0; // Se houver erro, `set_out` será um conjunto vazio.
	// if (set_a->size == MAX_SIZE) return FALSE;

	for (i = 0; i < set_a->size; ++i)
		set_out->elementos[i] = set_a->elementos[i];

	for (i = 0; i < set_b->size; ++i)

		if (!_is_on_set(set_b->elementos[i], set_a)) {

			if (out_i >= MAX_SIZE)
				return FALSE;

			set_out->elementos[out_i] = set_b->elementos[i];
			++out_i;
		}

	set_out->size = out_i;

	return TRUE;
}


IntSet *intersection(IntSet *set_a, IntSet *set_b)
{
	int i, j;
	IntSet *set_out = new_set();

	for (i = 0; i < set_a->size; ++i)

		for (j = 0; j < set_b->size; ++j)

			if (set_a->elementos[i] == set_b->elementos[j]) {
				set_out->elementos[set_out->size] = set_a->elementos[i];
				(set_out->size)++;
			}

	return set_out;
}


IntSet *diff(IntSet *set_a, IntSet *set_b)
{
	int _is_on_set(int value, IntSet *set);
	int i;
	IntSet *set_out = new_set();

	for (i = 0; i < set_a->size; ++i)

		if (!_is_on_set(set_a->elementos[i], set_b)) {
			set_out->elementos[set_out->size] = set_a->elementos[i];
			(set_out->size)++;
		}

	return set_out;
}


int is_contained(IntSet *set_a, IntSet *set_b)
{
	if (set_a->size > set_b->size)
		return FALSE;

	int _is_on_set(int value, IntSet *set);
	int i;

	for (i = 0; i < set_a->size; ++i)

		if (!_is_on_set(set_a->elementos[i], set_b))
			return FALSE;

	return TRUE;
}


int complementary(IntSet *minor_set, IntSet *major_set, IntSet *set_out)
{
	if (!is_contained(minor_set, major_set))
		return FALSE;

	IntSet *set = new_set();
	set = diff(major_set, minor_set);
	*set_out = *set;

	return TRUE;
}


void print_set(IntSet *set)
{
	if (set->size == 0) {
		printf("{ }");
		return;
	}

	int i = 0;
	printf("{%d", set->elementos[i]);

	for (i = 1; i < set->size; ++i)
		printf(", %d", set->elementos[i]);

	printf("}");
}


// Função de apoio
/* Verifica se o valor está no conjunto. */
int _is_on_set(int value, IntSet *set)
{
	int i;

	for (i = 0; i < set->size; ++i)

		if (value == set->elementos[i])
			return TRUE;

	return FALSE;
}
