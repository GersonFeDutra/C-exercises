#include "utils.h"
#include "input_validate.h"
#include <inttypes.h>
// #include <locale.h>
#include <stdio.h>
#include <stdlib.h>

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


void test_add_student(Tree **tree)
{
	if (*tree == NULL) {
		PRINT_CLR("Árvore inexistente!\nNada será feito!\n", text_yellow);
		return;
	}

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


void test_get_tree_higher_node(Tree **tree)
{
	void *ret;

	switch (get_tree_higher_node(*tree, &ret)) {
		case NULL_ERROR: PRINT_CLR(NULL_TREE_MESSAGE, text_red) break;
		case EMPTY_ERROR: PRINT_CLR(EMPTY_TREE_MESSAGE, text_red) break;
		case OK: {
			Student student = (Student)ret;
			printf("O aluno com a maior matrícula na árvore é [%d]: {Nome: %s, Nota 1: %.1f, "
				   "Nota 2: %.1f}.\n",
				student->id, student->name, student->av1, student->av2);
		} break;
	}
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


void test_print_tree(Tree *tree)
{
	if (print_tree(tree) == NULL_ERROR)
		PRINT_CLR("Árvore Inexistente!\n", text_red)
}


void silent_reset(Tree **tree)
{
	free_nodes(*tree);

	if (*tree == NULL)
		return;

	free(*tree);
	*tree = NULL;
}


// Quantida de opções disponíveis.
#define N_OPTIONS 13
static const Option OPTIONS[] = {
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
	{.title = "Maior nó", .resolve = &test_get_tree_higher_node},
	{.title = "Menor nó (restrito)", .resolve = &test_get_tree_nearest_lower},
};

void get_options(const Option **r_options, uint8_t *r_n)
{
	// Option *options = (Option *)malloc(sizeof(Option) * n);
	*r_options = OPTIONS;
	*r_n = N_OPTIONS;
}
