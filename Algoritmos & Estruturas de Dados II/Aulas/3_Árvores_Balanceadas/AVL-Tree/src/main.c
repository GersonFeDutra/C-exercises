#include "input_validate.h"
#include "utils.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE "---------------------"
#define INPUT_MARKER ">>>"

#if defined(_WIN32) || defined(_WIN64)
#define PAUSE system("pause");
#endif
#ifndef PAUSE
#define PAUSE                                                                                      \
	printf("Pressione a tecla Enter para continuar...");                                           \
	while (getchar() != '\n') {                                                                    \
	}
#endif

// Clear the terminal
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
int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "Portuguese");
	uint8_t is_test_mode = false;
	uint8_t i;
	char test_flag[] = "-t";

	for (i = 0; i < argc; ++i)
		if (strcmp(argv[i], test_flag) == 0) {
			is_test_mode = true;
			break;
		}

	void test(Tree * nutz);
	void auto_test(Tree * nutz);

	printf("Bem vindo ao módulo de testes do Tipo Abstrato de Dados: Árvore AVL!\n\n");

	if (is_test_mode) {
		printf("O objetivo desse módulo é verificar as possibilidades de operações com essa "
			   "estrutura!\nAtualmente executando em ");
		fputs("modo automático!\n\n", text_bold(stdout));
		reset_colors(stdout);
	}
	else {
		printf("O objetivo desse módulo é verificar ");
		fputs("manualmente", text_bold(stdout));
		reset_colors(stdout);
		printf(" as possibilidades de operações com essa estrutura.\n\n");
	}

	PAUSE
	CLEAR
	Tree *nutz = NULL;

	if (is_test_mode)
		auto_test(nutz);

	test(nutz);
	silent_reset(&nutz);
	printf("Fim da execução!\n");

	return 0;
}


/* O loop-principal (ciclo de vida do programa) ocorre aqui. */
void test(Tree *nutz)
{
	int8_t i;
	uint8_t opts;
	const Option *options;
	get_options(&options, &opts);

	while (1) {
		printf(LINE " Menu de testes " LINE "\n");

		for (i = 0; i < opts; ++i)
			printf("%d - %s\n", i + 1, options[i].title);

		printf("0 - Sair\n");
		int choice = input_integer_range(0, opts, INPUT_MARKER,
			"Entrada inválida! Tente novamente:", INPUT_MARKER,
			"Entrada inválida! Tente novamente:");

		if (choice == 0)
			return;

		options[choice - 1].resolve(&nutz);
		test_print_tree(&nutz);
		PAUSE
		CLEAR
	}
}


void auto_test(Tree *nutz)
{
	// char *names[125] = ;

	struct auto_source source = {
		.possible_names =
			{
				"Gold D. Roger",
				"Portgas D. Rouge",
				"Monkey D. Luffy",
				"Portgas D. Ace",
				"Trafalgar D. Water Law",
				"Monkey D. Garp",
				"Monkey D. Dragon",
				"Jaguar D. Saul",
				"Marshall D. Teach",
				"Con D. Oriano",
				"Go D. Usopp",
			},
		.possible_names_n = 11,
	};

	start_auto_test(source);
	test_create_tree(&nutz);

	uint8_t i = 0;
	for (i = 0; i < source.possible_names_n; ++i)
		auto_add_student(&nutz, i);

	finish_auto_test();
	printf(LINE "Árvore gerada" LINE "\n");
	test_print_tree(&nutz);
	PAUSE
	CLEAR
}
