#include "avl_tree.h"
#include <inttypes.h>

/* Informações sobre operações que a aplicação pode realizar. */
struct option {
	char title[125];
	void (*resolve)(Tree **);
} typedef Option;

struct auto_source {
	char *possible_names[125];
	uint8_t possible_names_n;
};

/* Retorna um array com todas as opções de operaçoẽs possíveis da aplicação. */
void get_options(const Option **r_options, uint8_t *r_n);

void silent_reset(Tree **tree);

void test_print_tree(Tree **tree);

/* Funções para testes automáticos. */

/* Função que deve ser chamada para iniciar o módulo de testes. Um vetor com os possíveis nomes
 * usados nos testes devem ser determinados.
 */
void start_auto_test(struct auto_source new);

/*  Função que deve ser chamada ao finalizar o uso do módulo de testes.
 * É importante que seja invocada para evitar possíveis vazamentos de memória.
 */
void finish_auto_test();

void test_create_tree(Tree **tree);

void test_clear_tree(Tree **tree);

void test_destroy_tree(Tree **tree);

void auto_add_student(Tree **tree, int32_t id);

void auto_remove_student(Tree **tree, int32_t id);
