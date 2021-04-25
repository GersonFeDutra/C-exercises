#include "binary_tree.h"
#include "input_validate.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>


#if defined(_WIN32) || defined(_WIN64)
#define PAUSE system("pause");
#endif
#ifndef PAUSE
#define PAUSE                                                                                      \
	printf("Pressione a tecla Enter para continuar...");                                           \
	while (getchar() != '\n') {                                                                    \
	}
#endif

#if defined(_WIN32) || defined(_WIN64)
#define CLEAR system("cls");
#endif
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
#define CLEAR system("clear");
#endif
#ifndef CLEAR
// ANSI consoles
#define CLEAR                                                                                      \
	printf("Pressione a tecla Enter para continuar...");                                           \
	while (getchar() != '\n') {                                                                    \
	}                                                                                              \
	printf("\e[1;1H\e[2J");
#endif

#define LINE "---------------------"
#define INPUT_MARKER ">>>"
#define NULL_TREE_MESSAGE "Erro! Árvore inexistente!\n"
#define EMPTY_TREE_MESSAGE "Erro! Árvore vazia!\n"
#define INVALID_INPUT_MESSAGE "Erro! Entrada inválida. Tente novamente:"
#define NEGATIVE_INPUT_MESSAGE "Erro! Entrada negativa. Tente novamente:"
#define INVALID_ID_MESSAGE "Erro! Matrícula inexistente!\n"

/*
░░░░░░░░░░░░░░░░░░░░   ░░░░░▄▄▀▀▀▀▀▀▀▀▀▄▄░░░░░
░░░░░░░░░░░░░░░░░░░░   ░░░░█░░░░░░░░░░░░░█░░░░
░░▄ ▀▄▄▀▄░░░░░░░░░░░   ░░░█░░░░░░░░░░▄▄▄░░█░░░
░█░░░░░░░░▀▄░░░░░░▄░   ░░░█░░▄▄▄░░▄░░███░░█░░░
█░░▀░░▀░░░░░▀▄▄░░█░█   ░░░▄█░▄░░░▀▀▀░░░▄░█▄░░░
█░▄░█▀░▄░░░░░░░▀▀░░█   ░░░█░░▀█▀█▀█▀█▀█▀░░█░░░
█░░▀▀▀▀░░░░░░░░░░░░█   ░░░▄██▄▄▀▀▀▀▀▀▀▄▄██▄░░░
█░░░░░░░░░░░░░░░░░░█   ░▄█░█▀▀█▀▀▀█▀▀▀█▀▀█░█▄░
█░░░░░░░░░░░░░░░░░░█   ▄▀░▄▄▀▄▄▀▀▀▄▀▀▀▄▄▀▄▄░▀▄
░█░░▄▄░░▄▄▄▄░░▄▄░░█░   █░░░░▀▄░█▄░░░▄█░▄▀░░░░█
░█░▄▀█░▄▀░░█░▄▀█░▄▀░   ▀▄▄░█░░█▄▄▄▄▄█░░█░▄▄▀
░░░░░░░░░░░░░░░░░░░░   ░░░▀██▄▄███████▄▄██▀ :D
*/
int main()
{
	setlocale(LC_ALL, "Portuguese");

	void test(void);

	printf(
		"Bem vindo ao módulo de testes do Tipo Abstrato de Dados: Árvore Binária Dinâmica!\n"
		"O objetivo desse módulo é verificar manualmente as possibilidades de operações com essa "
		"estrutura.\n\n"); /* Devido à enorme quantidade de casos possíveis ao operar árvores, não
	    fiz testes automáticos dessa vez... Decidí fazer o exercício um tanto "meta". */
	PAUSE
	CLEAR
	test();
	printf("Fim da execução!\n");

	return 0;
}


void test_create_tree(Tree **tree)
{
	if (*tree != NULL) {
		printf("Aviso! Árvore já existe, você deve destruir a árvore antes de criar uma nova.\n"
			   "Nada será feito!\n");
		return;
	}
	*tree = new_tree();

	if (*tree != NULL)
		printf("Árvore criada com sucesso!\n");
	else
		printf("Erro de memória ao alocar árvore!\n");
}


void test_clear_tree(Tree **tree)
{
	if (*tree == NULL) {
		printf("Aviso! Não é possível esvaziar uma árvore inexistente.\nNada será feito.\n");
		return;
	}
	if (is_empty_tree(*tree)) {
		printf("Aviso! Árvore já está vazia.\nNada será alterado.\n");
		return;
	}

	clear_tree(*tree);
	printf("Árvore esvaziada com sucesso!\n");
}


void test_destroy_tree(Tree **tree)
{
	if (*tree == NULL) {
		printf("Aviso! Árvore inexistente.\nNada será alterado.\n");
		return;
	}

	if (!is_empty_tree(*tree)) {
		clear_tree(*tree);
		printf("A árvore foi esvaziada!\n");
	}

	free(*tree);
	*tree = NULL;
	printf("Árvore eliminada com sucesso!\n");
}


void test_add_student(Tree **tree)
{
	if (*tree == NULL) {
		printf("Árvore inexistente!\nNada será feito!\n");
		return;
	}

	char INVALID_RANGE_MESSAGE[] = "Erro! Insira um valor entre 0 e 10:";
	struct student new;

	printf("Insira os dados do aluno:\n");
	printf("Nome: ");
	scanf("%s", new.name);
	while (getchar() != '\n') {
	}
	/* Nota `scanf` é perigoso, seu uso pode não funcionar como esperado, mas, em prol da
	conveniência, vou manter desse modo mesmo...
	<https://stackoverflow.com/questions/2430303/disadvantages-of-scanf#2430310> */
	new.av1 = input_integer_range(
		0, 10, "1° Nota:", INVALID_INPUT_MESSAGE, "1° Nota:", INVALID_RANGE_MESSAGE);
	new.av2 = input_integer_range(
		0, 10, "2° Nota:", INVALID_INPUT_MESSAGE, "2° Nota:", INVALID_RANGE_MESSAGE);

	int out;
	do {
		new.id = input_min_integer(
			0, "Matrícula:", INVALID_INPUT_MESSAGE, "Matrícula:", NEGATIVE_INPUT_MESSAGE);
		switch (out = insert_node(*tree, new)) {
			case INPUT_ERROR: printf("A matrícula indicada já está registarda na árvore!\n"); break;
			case NOT_OK: {
				printf("Erro de memória ao alocar nó!\n");
				return;
			};
				// case NULL_ERROR: return;
				/* Não verificamos esse caso, pois já o fizemos no topo dessa função. */
		}
	} while (out != OK);

	printf("Aluno inserido com sucesso!\n");
}


void test_remove_student(Tree **tree)
{
	printf("Insira a matrícula do aluno a ser removido:\n");
	switch (remove_node(*tree, input_min_integer(0, INPUT_MARKER, INVALID_INPUT_MESSAGE,
								   INPUT_MARKER, NEGATIVE_INPUT_MESSAGE))) {
		case NULL_ERROR: printf(NULL_TREE_MESSAGE); break;
		case EMPTY_ERROR: printf(EMPTY_TREE_MESSAGE); break;
		case NOT_OK: printf(INVALID_ID_MESSAGE); break;
		case OK: printf("Aluno removido com sucesso!\n"); break;
	}
}


void test_access_student(Tree **tree)
{
	struct student student;
	printf("Insira a matrícula do aluno a ser acessado:\n");

	switch (get_node(*tree,
		input_min_integer(
			0, INPUT_MARKER, INVALID_INPUT_MESSAGE, INPUT_MARKER, NEGATIVE_INPUT_MESSAGE),
		&student)) {
		case NULL_ERROR: printf(NULL_TREE_MESSAGE); break;
		case EMPTY_ERROR: printf(EMPTY_TREE_MESSAGE); break;
		case NOT_OK: printf(INVALID_ID_MESSAGE); break;
		case OK:
			printf("Aluno [%d]: {Nome: %s, Nota 1: %.1f, Nota 2: %.1f}.\n", student.id,
				student.name, student.av1, student.av2);
			break;
	}
}


void test_travel_tree(Tree **tree)
{
	if (*tree == NULL) {
		printf("Aviso! Não é possível percorrer uma árvore inexistente.\n");
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
		printf("Aviso: Árvore Inexistente!\n");
	else
		printf("Altura da árvore = %d\n", n);
}


void test_node_depth(Tree **tree)
{
	int n;
	printf("Insira a matrícula do aluno a ser acessado:\n");

	switch (n = node_depth(*tree, input_min_integer(0, INPUT_MARKER, INVALID_INPUT_MESSAGE,
									  INPUT_MARKER, NEGATIVE_INPUT_MESSAGE))) {
		case 0: printf("Aviso: Nó não foi encontrado!\n"); break;
		case NULL_ERROR: printf("Aviso: Árvore Inexistente!\n"); break;
		case EMPTY_ERROR: printf("Aviso: Árvore Vazia!\n"); break;
		default: printf("Altura do nó = %d\n", n);
	}
}


void test_node_count(Tree **tree)
{
	int n = node_count(*tree);

	if (n == NULL_ERROR)
		printf("Aviso! Árvore Inexistente!\n");
	else
		printf("Quantidade de nós da árvore = %d\n", n);
}


void test_get_tree_higher_node(Tree **tree)
{
	struct student student;

	switch (get_tree_higher_node(*tree, &student)) {
		case NULL_ERROR: printf(NULL_TREE_MESSAGE); break;
		case EMPTY_ERROR: printf(EMPTY_TREE_MESSAGE); break;
		case OK:
			printf("O aluno com a maior matrícula na árvore é [%d]: {Nome: %s, Nota 1: %.1f, "
				   "Nota 2: %.1f}.\n",
				student.id, student.name, student.av1, student.av2);
			break;
	}
}


void test_leaves_count(Tree **tree)
{
	int n = leaves_count(*tree);

	if (n == NULL_ERROR)
		printf("Aviso! Árvore Inexistente!\n");
	else
		printf("Quantidade de folhas da árvore = %d\n", n);
}


void test_get_tree_nearest_lower(Tree **tree)
{
	struct student student;

	printf("Insira um valor mínimo:\n");
	switch (get_tree_nearest_lower(*tree,
		input_min_integer(
			0, INPUT_MARKER, INVALID_INPUT_MESSAGE, INPUT_MARKER, NEGATIVE_INPUT_MESSAGE),
		&student)) {
		case NULL_ERROR: printf(NULL_TREE_MESSAGE); break;
		case EMPTY_ERROR: printf(EMPTY_TREE_MESSAGE); break;
		case NOT_OK:
			printf("Não foi encontrado um aluno cujo matrícula é maior ou igual a esse valor "
				   "mínimo.\n");
			break;
		case OK:
			printf("Menor aluno (maior ou igual ao limite indicado) [%d]:\n"
				   "{Nome: %s, Nota 1: %.1f, Nota 2: %.1f}.\n",
				student.id, student.name, student.av1, student.av2);
			break;
	}
}


void test_get_tree_nth_lower(Tree **tree)
{
	struct student student;
	int n;

	printf("Insira um valor inteiro, maior que zero, para obter o n-ésimo menor:\n");
	n = input_min_integer(
		1, INPUT_MARKER, INVALID_INPUT_MESSAGE, INPUT_MARKER, INVALID_INPUT_MESSAGE);

	switch (get_tree_nth_lower(*tree, n, &student)) {
		case NULL_ERROR: printf(NULL_TREE_MESSAGE); break;
		case EMPTY_ERROR: printf(EMPTY_TREE_MESSAGE); break;
		// case INPUT_ERROR: printf("Erro\n"); break;
		// Não checamos esse caso pois sabemos que jamais passaremos uma entrada negativa.
		case NOT_OK: printf("A árvore possui menos de %d nós.\n", n); break;
		case OK:
			printf("%d° menor aluno [%d]:\n{Nome: %s, Nota 1: %.1f, Nota 2: %.1f}.\n", n,
				student.id, student.name, student.av1, student.av2);
			break;
	}
}


void test()
{
	struct option {
		char title[125];
		void (*resolve)(Tree **);
	} typedef Option;

	static const int OPTS = 14;
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
		{.title = "N-ésimo menor", .resolve = &test_get_tree_nth_lower},
	};
	Tree *nutz = NULL;
	int i;

	while (1) {
		printf(LINE " Menu de testes " LINE "\n");

		for (i = 0; i < OPTS; ++i)
			printf("%d - %s\n", i + 1, OPTIONS[i].title);

		printf("0 - Sair\n");
		int choice = input_integer_range(0, OPTS, INPUT_MARKER,
			"Entrada inválida! Tente novamente:", INPUT_MARKER,
			"Entrada inválida! Tente novamente:");

		if (choice == 0)
			return;

		OPTIONS[choice - 1].resolve(&nutz);
		PAUSE
		CLEAR
	}
}
