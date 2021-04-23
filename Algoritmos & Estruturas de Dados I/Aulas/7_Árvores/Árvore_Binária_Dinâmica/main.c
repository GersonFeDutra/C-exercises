#include "arvore_binaria.h"
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


int main()
{
	setlocale(LC_ALL, "Portuguese");

	void test(void);

	printf(
		"Bem vindo ao módulo de testes do Tipo Abstrato de Dados: Árvore Binária Dinâmica!\n"
		"O objetivo desse módulo é verificar manualmente as possibilidades de operações com essa "
		"estrutura\n\n"); /* Devido à enorme quantidade de casos possíveis ao operar árvores, não
	    fiz testes automáticos dessa vez... Decidí fazer o exercício um tanto "meta". */
	PAUSE
	CLEAR
	test();
	printf("Fim da execução!\n");

	return 0;
}


void test_criar_arvore(Arvore **arvore)
{
	if (*arvore != NULL) {
		printf("Aviso! Árvore já existe, você deve destruir a árvore antes de criar uma nova.\n"
			   "Nada será feito!\n");
		return;
	}
	*arvore = criar_arvore();

	if (*arvore != NULL)
		printf("Árvore criada com sucesso!\n");
	else
		printf("Erro de memória ao alocar árvore!\n");
}


void test_esvaziar_arvore(Arvore **arvore)
{
	if (*arvore == NULL) {
		printf("Aviso! Não é possível esvaziar uma árvore inexistente.\nNada será feito.\n");
		return;
	}
	if (vazia(*arvore)) {
		printf("Aviso! Árvore já está vazia.\nNada será alterado.\n");
		return;
	}

	limpar_arvore(*arvore);
	printf("Árvore esvaziada com sucesso!\n");
}


void test_destruir_arvore(Arvore **arvore)
{
	if (*arvore == NULL) {
		printf("Aviso! Árvore inexistente.\nNada será alterado.\n");
		return;
	}

	if (!vazia(*arvore)) {
		limpar_arvore(*arvore);
		printf("A árvore foi esvaziada!\n");
	}

	free(*arvore);
	*arvore = NULL;
	printf("Árvore eliminada com sucesso!\n");
}


void test_adicionar_aluno(Arvore **arvore)
{
	if (*arvore == NULL) {
		printf("Árvore inexistente!\nNada será feito!\n");
		return;
	}

	struct aluno novo;
	printf("Insira os dados do aluno:\n");
	printf("Nome: ");
	scanf("%s", novo.nome);
	while (getchar() != '\n') {
	}
	/* Nota `scanf` é perigoso, seu uso pode não funcionar como esperado, mas, em prol da
	conveniência, vou manter desse modo mesmo...
	<https://stackoverflow.com/questions/2430303/disadvantages-of-scanf#2430310> */
	novo.av1 = input_integer_range(0, 10, "1° Nota:", "Erro! Entrada inválida. Tente novamente:",
		"1° Nota:", "Erro! Insira um valor entre 0 e 10:");
	novo.av2 = input_integer_range(0, 10, "2° Nota:", "Erro! Entrada inválida. Tente novamente:",
		"2° Nota:", "Erro! Insira um valor entre 0 e 10:");

	int out;
	do {
		novo.matricula =
			input_min_integer(0, "Matrícula:", "Erro! Entrada inválida. Tente novamente:",
				"Matrícula:", "Erro! Entrada negativa. Tente novamente:");
		switch (out = inserir_no(*arvore, novo)) {
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


void test_remover_aluno(Arvore **arvore)
{
	printf("Insira a matrícula do aluno a ser removido:\n");
	switch (remover_no(
		*arvore, input_min_integer(0, ">>>", "Erro! Entrada inválida. Tente novamente:", ">>>",
					 "Erro! Entrada negativa. Tente novamente:"))) {
		case NULL_ERROR: printf("Erro! Árvore Inexistente.\n"); break;
		case EMPTY_ERROR: printf("Erro! Árvore vazia!\n"); break;
		case NOT_OK: printf("Erro! Matrícula inexistente!\n"); break;
		case OK: printf("Aluno removido com sucesso!\n"); break;
	}
}


void test_acessar_aluno(Arvore **arvore)
{
	struct aluno aluno;
	printf("Insira a matrícula do aluno a ser acessado:\n");

	switch (acessar_no(*arvore,
		input_min_integer(0, ">>>", "Erro! Entrada inválida. Tente novamente:", ">>>",
			"Erro! Entrada negativa. Tente novamente:"),
		&aluno)) {
		case NULL_ERROR: printf("Erro! Árvore Inexistente.\n"); break;
		case EMPTY_ERROR: printf("Erro! Árvore vazia!\n"); break;
		case NOT_OK: printf("Erro! Matrícula inexistente!\n"); break;
		case OK:
			printf("Aluno [%d]: {Nome: %s, Nota 1: %.1f, Nota 2: %.1f}.\n", aluno.matricula,
				aluno.nome, aluno.av1, aluno.av2);
			break;
	}
}


void test_percorrer_arvore(Arvore **arvore)
{
	if (*arvore == NULL) {
		printf("Aviso! Não é possível percorrer uma árvore inexistente.\n");
		return;
	}

	printf("Escolha uma ordem de acesso:\n"
		   "-1 - Pré-Ordem (imprime os elementos na ordem em que os nós são acessados)\n"
		   " 0 - Em Ordem (imprime os nós da esquerda primeiro)\n"
		   " 1 - Pós-Ordem (imprime os nós de ambos os lados, antes de imprimir um nó pai)\n");

	int ordem = input_integer_range(-1, 1, ">>>", "Entrada inválida! Tente novamente:", ">>>",
		"Entrada inválida! Tente novamente:");
	printf("{ ");
	percorrer(*arvore, ordem);
	printf("}\n");
}


void test_altura_arvore(Arvore **arvore)
{
	int n = altura(*arvore);

	if (n == NULL_ERROR)
		printf("Aviso: Árvore Inexistente!\n");
	else
		printf("Altura da árvore = %d\n", n);
}


void test_altura_no(Arvore **arvore)
{
	int n;
	printf("Insira a matrícula do aluno a ser acessado:\n");

	switch (n = altura_no(*arvore,
				input_min_integer(0, ">>>", "Erro! Entrada inválida. Tente novamente:", ">>>",
					"Erro! Entrada negativa. Tente novamente:"))) {
		case 0: printf("Aviso: Nó não foi encontrado!\n"); break;
		case NULL_ERROR: printf("Aviso: Árvore Inexistente!\n"); break;
		case EMPTY_ERROR: printf("Aviso: Árvore Vazia!\n"); break;
		default: printf("Altura do nó = %d\n", n);
	}
}


void test_quantidade_nos(Arvore **arvore)
{
	int n = quantidade_nos(*arvore);

	if (n == NULL_ERROR)
		printf("Aviso! Árvore Inexistente!\n");
	else
		printf("Quantidade de nós da árvore = %d\n", n);
}


void test()
{
	struct option {
		char title[125];
		void (*resolve)(Arvore **);
	} typedef Option;

	static const int OPTS = 10;
	static const Option OPTIONS[] = {
		{.title = "Criar árvore", .resolve = &test_criar_arvore},
		{.title = "Esvaziar árvore", .resolve = &test_esvaziar_arvore},
		{.title = "Destruir árvore", .resolve = &test_destruir_arvore},
		{.title = "Adicionar aluno", .resolve = &test_adicionar_aluno},
		{.title = "Remover aluno", .resolve = &test_remover_aluno},
		{.title = "Acessar aluno", .resolve = &test_acessar_aluno},
		{.title = "Percorrer árvore", .resolve = &test_percorrer_arvore},
		{.title = "Altura da árvore", .resolve = &test_altura_arvore},
		{.title = "Altura do nó", .resolve = &test_altura_no},
		{.title = "Quantidade de nós", .resolve = &test_quantidade_nos},
	};
	Arvore *nozes = NULL;
	int i;

	while (1) {
		printf(LINE " Menu de testes " LINE "\n");

		for (i = 0; i < OPTS; ++i)
			printf("%d - %s\n", i + 1, OPTIONS[i].title);

		printf("0 - Sair\n");
		int choice = input_integer_range(0, OPTS, ">>>",
			"Entrada inválida! Tente novamente:", ">>>", "Entrada inválida! Tente novamente:");

		if (choice == 0)
			return;

		OPTIONS[choice - 1].resolve(&nozes);
		PAUSE
		CLEAR
	}
}
