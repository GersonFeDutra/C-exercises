#include "avl_tree.h"
#include <inttypes.h>

/* Informações sobre operações que a aplicação pode realizar. */
struct option {
	char title[125];
	void (*resolve)(Tree **);
} typedef Option;

/* Retorna um array com todas as opções de operaçoẽs possíveis da aplicação. */
void get_options(const Option **r_options, uint8_t *r_n);

void silent_reset(Tree **tree);
