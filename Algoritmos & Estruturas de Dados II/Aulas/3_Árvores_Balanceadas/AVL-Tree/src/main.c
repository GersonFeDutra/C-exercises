#include "input_validate.h"
#include "utils.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

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
int main()
{
	setlocale(LC_ALL, "Portuguese");

	void test(void);

	printf(
		"Bem vindo ao módulo de testes do Tipo Abstrato de Dados: Árvore AVL!\n"
		"O objetivo desse módulo é verificar manualmente as possibilidades de operações com essa "
		"estrutura.\n\n");
	PAUSE
	CLEAR
	test();
	printf("Fim da execução!\n");

	return 0;
}


/* O loop-principal (ciclo de vida do programa) ocorre aqui. */
void test()
{
	uint8_t opts;
	const Option *options;
	get_options(&options, &opts);

	Tree *nutz = NULL;
	int i;

	while (1) {
		printf(LINE " Menu de testes " LINE "\n");

		for (i = 0; i < opts; ++i)
			printf("%d - %s\n", i + 1, options[i].title);

		printf("0 - Sair\n");
		int choice = input_integer_range(0, opts, INPUT_MARKER,
			"Entrada inválida! Tente novamente:", INPUT_MARKER,
			"Entrada inválida! Tente novamente:");

		if (choice == 0) {
			silent_reset(&nutz);
			return;
		}
		options[choice - 1].resolve(&nutz);
		PAUSE
		CLEAR
	}
}
