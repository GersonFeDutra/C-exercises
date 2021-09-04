#include "utils.h"
#include "input_validate.h"
#include <inttypes.h>
// #include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_MARKER ">>>"
#define NULL_TREE_MESSAGE "Erro! Árvore inexistente!\n"
#define EMPTY_TREE_MESSAGE "Erro! Árvore vazia!\n"
#define INVALID_INPUT_MESSAGE "Erro! Entrada inválida. Tente novamente:"
#define NEGATIVE_INPUT_MESSAGE "Erro! Entrada negativa. Tente novamente:"
#define INVALID_ID_MESSAGE "Erro! Matrícula inexistente!\n"

// Imprime a stream de texto colorida no console.
#define PRINT_CLR(STREAM, TEXT_FUNC)                                                               \
	{                                                                                              \
		fputs(STREAM, TEXT_FUNC(stdout));                                                          \
		reset_colors(stdout);                                                                      \
	}

#define DO_NOTHING(TREE)                                                                           \
	if (*TREE == NULL) {                                                                           \
		PRINT_CLR("Árvore inexistente!\nNada será feito!\n", text_yellow);                         \
		return;                                                                                    \
	}

#define CHECK_TREE_METHOD(METHOD, CASE_OK)                                                         \
	switch (METHOD) {                                                                              \
		case NULL_ERROR: PRINT_CLR(NULL_TREE_MESSAGE, text_red) break;                             \
		case EMPTY_ERROR: PRINT_CLR(EMPTY_TREE_MESSAGE, text_red) break;                           \
		case OK: CASE_OK break;                                                                    \
	}

struct student {
	int32_t id;
	char name[125];
	float av1;
	float av2;
} typedef *Student;


void test_create_tree(Tree **tree)
{
	if (*tree != NULL) {
		PRINT_CLR("Aviso! Árvore já existe, você deve destruir a árvore antes de criar uma nova.\n"
				  "Nada será feito!\n",
			text_yellow)
		return;
	}
	*tree = new_tree();

	if (*tree != NULL)
		PRINT_CLR("Árvore criada com sucesso!\n", text_green)
	else
		PRINT_CLR("Erro de memória ao alocar árvore!\n", text_red)
}


void test_clear_tree(Tree **tree)
{
	if (*tree == NULL) {
		PRINT_CLR("Aviso! Não é possível esvaziar uma árvore inexistente.\nNada será feito.\n",
			text_yellow)
		return;
	}
	if (is_empty_tree(*tree)) {
		PRINT_CLR("Aviso! Árvore já está vazia.\nNada será alterado.\n", text_yellow)
		return;
	}

	free_nodes(*tree);
	PRINT_CLR("Árvore esvaziada com sucesso!\n", text_green);
}


void test_destroy_tree(Tree **tree)
{
	if (*tree == NULL) {
		PRINT_CLR("Aviso! Árvore inexistente.\nNada será alterado.\n", text_yellow)
		return;
	}

	if (!is_empty_tree(*tree)) {
		free_nodes(*tree);
		PRINT_CLR("A árvore foi esvaziada!\n", text_cyan);
	}

	free(*tree);
	*tree = NULL;
	PRINT_CLR("Árvore eliminada com sucesso!\n", text_green)
}


/* Métodos manuais. */

void test_add_student(Tree **tree)
{
	DO_NOTHING(tree)
	char INVALID_RANGE_MESSAGE[] = "Erro! Insira um valor entre 0 e 10:";
	Student new = (Student)malloc(sizeof(struct student));

	printf("Insira os dados do aluno:\n");
	PRINT_CLR("Nome: ", text_blue)
	scanf("%s", new->name);
	while (getchar() != '\n') {
	}
	/* Nota `scanf` é perigoso, seu uso pode não funcionar como esperado, mas, em prol da
	conveniência, vou manter desse modo mesmo...
	<https://stackoverflow.com/questions/2430303/disadvantages-of-scanf#2430310> */
	new->av1 = input_integer_range(
		0, 10, "1° Nota:", INVALID_INPUT_MESSAGE, "1° Nota:", INVALID_RANGE_MESSAGE);
	new->av2 = input_integer_range(
		0, 10, "2° Nota:", INVALID_INPUT_MESSAGE, "2° Nota:", INVALID_RANGE_MESSAGE);

	int out;
	do {
		new->id = input_min_integer(
			0, "Matrícula:", INVALID_INPUT_MESSAGE, "Matrícula:", NEGATIVE_INPUT_MESSAGE);
		switch (out = insert_node(*tree, new, new->id)) {
			case INPUT_ERROR:
				PRINT_CLR("A matrícula indicada já está registarda na árvore!\n", text_yellow)
				break;
			case NOT_OK: {
				PRINT_CLR("Erro de memória ao alocar nó!\n", text_red)
				free(new);
				return;
			};
				// case NULL_ERROR: return;
				/* Não verificamos esse caso, pois já o fizemos no topo dessa função. */
		}
	} while (out != OK);

	PRINT_CLR("Aluno inserido com sucesso!\n", text_green)
}


void test_remove_student(Tree **tree)
{
	printf("Insira a matrícula do aluno a ser removido:\n");
	switch (free_node(*tree, input_min_integer(0, INPUT_MARKER, INVALID_INPUT_MESSAGE, INPUT_MARKER,
								 NEGATIVE_INPUT_MESSAGE))) {
		case NULL_ERROR: PRINT_CLR(NULL_TREE_MESSAGE, text_red) break;
		case EMPTY_ERROR: PRINT_CLR(EMPTY_TREE_MESSAGE, text_red) break;
		case NOT_OK: PRINT_CLR(INVALID_ID_MESSAGE, text_red) break;
		case OK: PRINT_CLR("Aluno removido com sucesso!\n", text_green) break;
	}
}


void test_access_student(Tree **tree)
{
	void *ret;
	printf("Insira a matrícula do aluno a ser acessado:\n");

	switch (get_node(*tree,
		input_min_integer(
			0, INPUT_MARKER, INVALID_INPUT_MESSAGE, INPUT_MARKER, NEGATIVE_INPUT_MESSAGE),
		&ret)) {
		case NULL_ERROR: PRINT_CLR(NULL_TREE_MESSAGE, text_red) break;
		case EMPTY_ERROR: PRINT_CLR(EMPTY_TREE_MESSAGE, text_red) break;
		case NOT_OK: PRINT_CLR(INVALID_ID_MESSAGE, text_red) break;
		case OK: {
			Student student = (Student)ret;
			printf("Aluno [%d]: {Nome: %s, Nota 1: %.1f, Nota 2: %.1f}.\n", student->id,
				student->name, student->av1, student->av2);
		} break;
	}
}


void test_travel_tree(Tree **tree)
{
	if (*tree == NULL) {
		PRINT_CLR("Aviso! Não é possível percorrer uma árvore inexistente.\n", text_yellow)
		return;
	}

	printf("Escolha uma ordem de acesso:\n"
		   "-1 - Pré-Ordem (imprime os elementos na ordem em que os nós são acessados)\n"
		   " 0 - Em Ordem (imprime os nós da esquerda primeiro)\n"
		   " 1 - Pós-Ordem (imprime os nós de ambos os lados, antes de imprimir um nó pai)\n");

	int ordem = input_integer_range(-1, 1, INPUT_MARKER,
		"Entrada inválida! Tente novamente:", INPUT_MARKER, "Entrada inválida! Tente novamente:");
	printf("{ ");
	travel_tree(*tree, ordem);
	printf("}\n");
}


void test_tree_depth(Tree **tree)
{
	int n = tree_depth(*tree);

	if (n == NULL_ERROR)
		PRINT_CLR("Aviso: Árvore Inexistente!\n", text_yellow)
	else
		printf("Altura da árvore = %d\n", n);
}


void test_node_depth(Tree **tree)
{
	int n;
	printf("Insira a matrícula do aluno a ser acessado:\n");

	switch (n = node_depth(*tree, input_min_integer(0, INPUT_MARKER, INVALID_INPUT_MESSAGE,
									  INPUT_MARKER, NEGATIVE_INPUT_MESSAGE))) {
		case 0: PRINT_CLR("Aviso: Nó não foi encontrado!\n", text_yellow) break;
		case NULL_ERROR: PRINT_CLR("Aviso: Árvore Inexistente!\n", text_yellow) break;
		case EMPTY_ERROR: PRINT_CLR("Aviso: Árvore Vazia!\n", text_yellow) break;
		default: printf("Altura do nó = %d\n", n);
	}
}


void test_node_count(Tree **tree)
{
	int n = node_count(*tree);

	if (n == NULL_ERROR)
		PRINT_CLR("Aviso! Árvore Inexistente!\n", text_yellow)
	else
		printf("Quantidade de nós da árvore = %d\n", n);
}


void test_get_tree_max_node(Tree **tree)
{
	void *ret;

	CHECK_TREE_METHOD(get_tree_max_node(*tree, &ret), {
		Student student = (Student)ret;
		printf("O aluno com a maior matrícula na árvore é [%d]: "
			   "{Nome: %s, Nota 1: %.1f, Nota 2: %.1f}.\n",
			student->id, student->name, student->av1, student->av2);
	})
}


void test_get_tree_min_node(Tree **tree)
{
	void *ret;

	CHECK_TREE_METHOD(get_tree_min_node(*tree, &ret), {
		Student student = (Student)ret;
		printf("O aluno com a menor matrícula na árvore é [%d]: "
			   "{Nome: %s, Nota 1: %.1f, Nota 2: %.1f}.\n",
			student->id, student->name, student->av1, student->av2);
	})
}


void test_leaves_count(Tree **tree)
{
	int n = leaves_count(*tree);

	if (n == NULL_ERROR)
		PRINT_CLR("Aviso! Árvore Inexistente!\n", text_yellow)
	else
		printf("Quantidade de folhas da árvore = %d\n", n);
}


void test_get_tree_nearest_lower(Tree **tree)
{
	void *ret;

	printf("Insira um valor mínimo:\n");
	switch (get_tree_nearest_lower(*tree,
		input_min_integer(
			0, INPUT_MARKER, INVALID_INPUT_MESSAGE, INPUT_MARKER, NEGATIVE_INPUT_MESSAGE),
		&ret)) {
		case NULL_ERROR: PRINT_CLR(NULL_TREE_MESSAGE, text_red) break;
		case EMPTY_ERROR: PRINT_CLR(EMPTY_TREE_MESSAGE, text_red) break;
		case NOT_OK:
			printf("Não foi encontrado um aluno cujo matrícula é maior ou igual a esse valor "
				   "mínimo.\n");
			break;
		case OK: {
			Student student = (Student)ret;
			printf("Menor aluno (maior ou igual ao limite indicado) [%d]:\n"
				   "{Nome: %s, Nota 1: %.1f, Nota 2: %.1f}.\n",
				student->id, student->name, student->av1, student->av2);
		} break;
	}
}


void test_print_tree(Tree **tree)
{
	if (print_tree(*tree) == NULL_ERROR)
		PRINT_CLR("Árvore Inexistente!\n", text_red)
}


void do_nothing(Tree **tree)
{
}


void silent_reset(Tree **tree)
{
	free_nodes(*tree);

	if (*tree == NULL)
		return;

	free(*tree);
	*tree = NULL;
}


/* Testes automáticos. */

// Guarda uma lista de referências para fácil deslocamento dos elementos.
static struct generator {
	struct auto_source source;
	uint8_t *availlable_names;
	uint8_t availlable_n;
} generator = {.source = {NULL, 0}, .availlable_names = NULL, .availlable_n = 0};

#define CHECK_MODULE_STARTED                                                                       \
	if (generator.source.possible_names_n == 0) {                                                  \
		PRINT_CLR("Erro! Módulo de testes automatizados não inicializada.\n", text_red)            \
		PRINT_CLR("Chamar o método `start_auto_test`\n", text_yellow)                              \
		return;                                                                                    \
	}


void auto_add_student(Tree **tree, int32_t id)
{
	CHECK_MODULE_STARTED
	DO_NOTHING(tree)
	Student new = (Student)malloc(sizeof(struct student));

	if (generator.availlable_n == 0) {
		PRINT_CLR(
			"Aviso: Fonte de nomes esvaziada! Não é possível continuar a geração", text_yellow);
		free(new);
		return;
	}

	// Escolhe um nome aleatória e marca-o como usado (removendo-o do vetor de disponíveis).
	uint8_t i = rand() % generator.availlable_n;
	strcpy(new->name, generator.source.possible_names[generator.availlable_names[i]]);
	generator.availlable_names[i] = generator.availlable_names[generator.availlable_n - 1];
	// Note que não necessariamente temos de removê-lo, apenas sobrescrever o seu valor com o último
	// elemento do vetor. Como o tamanho teórico será removido, economizamos no processamento. :D

	new->av1 = rand() % 10;
	new->av2 = rand() % 10;
	new->id = id;

	// printf("Inserindo aluno:");
	// sprintf(text_blue(stdout), "Nome: %s", new->name);
	// sprintf(text_blue(stdout), "1° Nota: %d", new->av1);
	// sprintf(text_blue(stdout), "2° Nota: %d", new->av2);
	// sprintf(text_blue(stdout), "Matrícula: %d", new->id);
	// reset_colors(stdout);

	switch (insert_node(*tree, new, new->id)) {
		case INPUT_ERROR: {
			// PRINT_CLR("A matrícula indicada já está registarda na árvore!\n", text_yellow)
			return;
		} break;
		case NOT_OK: {
			// PRINT_CLR("Erro de memória ao alocar nó!\n", text_red)
			free(new);
			return;
		};
	}
	// PRINT_CLR("Aluno inserido com sucesso!\n", text_green)
}


void auto_remove_student(Tree **tree, int32_t id)
{
	CHECK_MODULE_STARTED
	printf("Tentando remover aluno de mátricula [%d]:\n", id);
	switch (free_node(*tree, id)) {
		case NULL_ERROR: PRINT_CLR(NULL_TREE_MESSAGE, text_red) break;
		case EMPTY_ERROR: PRINT_CLR(EMPTY_TREE_MESSAGE, text_red) break;
		case NOT_OK: PRINT_CLR(INVALID_ID_MESSAGE, text_red) break;
		case OK: PRINT_CLR("Aluno removido com sucesso!\n", text_green) break;
	}
}


// Quantida de opções disponíveis.
#define N_OPTIONS 15
static const Option OPTIONS[] = {
	{.title = "Imprimir árvore", .resolve = &do_nothing},
	{.title = "Criar árvore", .resolve = &test_create_tree},
	{.title = "Esvaziar árvore", .resolve = &test_clear_tree},
	{.title = "Destruir árvore", .resolve = &test_destroy_tree},
	{.title = "Adicionar aluno", .resolve = &test_add_student},
	{.title = "Remover aluno", .resolve = &test_remove_student},
	{.title = "Acessar aluno", .resolve = &test_access_student},
	{.title = "Percorrer árvore", .resolve = &test_travel_tree},
	{.title = "Altura da árvore", .resolve = &test_tree_depth},
	{.title = "Altura do nó", .resolve = &test_node_depth},
	{.title = "Quantidade de nós", .resolve = &test_node_count},
	{.title = "Quantidade de folhas", .resolve = &test_leaves_count},
	{.title = "Maior nó", .resolve = &test_get_tree_max_node},
	{.title = "Menor nó", .resolve = &test_get_tree_min_node},
	{.title = "Menor nó (restrito)", .resolve = &test_get_tree_nearest_lower},
};

void get_options(const Option **r_options, uint8_t *r_n)
{
	// Option *options = (Option *)malloc(sizeof(Option) * n);
	*r_options = OPTIONS;
	*r_n = N_OPTIONS;
}


void start_auto_test(struct auto_source new)
{
	if (new.possible_names_n == 0 || new.possible_names == NULL) {
		PRINT_CLR("Erro! fonte de dados auto-gerados não foi determinada.\n", text_red)
		return;
	}

	generator.source = new;
	generator.availlable_names = (uint8_t *)malloc(sizeof(uint8_t) * new.possible_names_n);
	generator.availlable_n = new.possible_names_n;

	uint8_t i;
	for (i = 0; i < new.possible_names_n; ++i)
		generator.availlable_names[i] = 0;
}


void finish_auto_test()
{
	if (generator.availlable_names != NULL) {
		free(generator.availlable_names);
		generator.availlable_names = NULL;
		generator.availlable_n = 0;
	}

	generator.source.possible_names_n = 0;
}
