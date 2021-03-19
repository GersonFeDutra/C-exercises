#include "lista.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MENSAGEM_LISTA_INEXISTENTE "Erro: Lista inexistente!\n"
#define MENSAGEM_INSERÇÃO_SUCESSO "Aluno inserido com sucesso!\n"
#define OK_MESSAGE_ACCESS "Acesso realizado com sucesso!\n"
#define NOT_OK_MESSAGE_ACCESS "Não foi possível completar o acesso!\n"
#define LINE "--------------------"


int main()
{
	setlocale(LC_ALL, "Portuguese");

	Lista *turma = criar();

	// printf("Lista não existe.\n");
	// printf("Lista vazia!\n");

	void test_sample(Lista *);
	void preencher_lista(Lista * turma, char nomes[][8], int size);
	int i;
	char nomes[][8] = {"Roberto", "Dumont", "Pedro"};

	test_sample(NULL);

	for (i = 1; i < 3; ++i) {

		preencher_lista(turma, nomes, i);
		test_sample(turma);
		turma = criar();
	}

	void test(void);
	printf("\n");
	test();

	return 0;
}

/* Preenche uma lista de alunos com os nomes passados. */
void preencher_lista(Lista *turma, char nomes[][8], int size)
{
	int i;
	struct aluno aluno;

	for (i = 0; i < size; ++i) {
		aluno.matricula = 10 * (i + 1);
		strcpy(aluno.nome, nomes[i]);

		if (inserir_inicio(turma, aluno) == NULL_ERROR)
			printf("Erro: Lista inexistente!\n");
	}
}


void test()
{
	void print_lista(Lista *);
	void print_error(int flag, char ok_message[], char not_ok_message[]);
	const int ENTRIES = 4;

	int i;
	// Caches para concatenação de strings.
	char ok_message[160];
	char not_ok_message[160];
	char nomes[][8] = {"Roberto", "Dumont", "Pedro", "Gerson"};
	struct aluno aluno;
	Lista *turma = criar();

	/* Coleta de dados */
	preencher_lista(turma, nomes, ENTRIES);

	// Como a inserção foi realizada no início, "Gerson" deve ser o 1º nome e "Roberto" o último.
	printf(LINE " Lista inicializada " LINE "\n");
	print_lista(turma);

	/* Operações */

	printf(LINE " Operações " LINE "\n");
	print_error(acessar_por_indice(turma, 0, &aluno), "", "");
	sprintf(ok_message, "Primeiro aluno [%s] removido com sucesso!\n", aluno.nome);
	print_error(remover_inicio(turma), ok_message, "");
	print_lista(turma);

	// Deve dar erro
	print_error(acessar_por_indice(turma, 7, &aluno), "", "Erro ao acessar índice 7 da lista.\n");

	// Usei a atribuição na mesma linha da chamada `print_error()` só pq eu posso mesmo! :P
	print_error((i = acessar_por_indice(turma, -4, &aluno)), "", ""); // Deve dar erro

	print_error((i = acessar_por_indice(turma, 2, &aluno)),
		"Índice 2 acessado com sucesso: ", "Erro ao acessar índice 2.\n");

	if (i == OK)
		printf("(%d) %s\n", aluno.matricula, aluno.nome);

	print_error(acessar_por_matricula(turma, 70, &aluno), "",
		"Matrícula [70] não foi encontrada.\n"); // Deve dar erro
	print_error(acessar_por_matricula(turma, 30, &aluno),
		"Matrícula de número [30] acessada com sucesso!\n", ""); // Acessando matricula 30
	printf("Aluno [%d] %s.\n", aluno.matricula, aluno.nome);

	/* Mais inserções */

	printf(LINE " Inserções " LINE "\n");

	strcpy(aluno.nome, "Marx");
	aluno.matricula = (ENTRIES + 1) * 10;
	printf("Inserindo aluno [%s], com a matrícula de número [%d], no final da lista...\n",
		aluno.nome, aluno.matricula);
	print_error(inserir_fim(turma, aluno), MENSAGEM_INSERÇÃO_SUCESSO, "");
	print_lista(turma);

	strcpy(aluno.nome, "Ju");
	aluno.matricula = (ENTRIES + 2) * 10;
	printf("Inserindo aluno [%s] na terceira posição...\n", aluno.nome);
	print_error(inserir_meio(turma, aluno, 2), MENSAGEM_INSERÇÃO_SUCESSO, "");
	print_lista(turma);

	/* Remoções */

	printf(LINE " Remoções " LINE "\n");
	sprintf(ok_message, "Aluno de matrícula [%d] removido com sucesso.\n", 20);
	sprintf(not_ok_message, "Não foi possível remover matrícula [%d].\n", 20);
	print_error(remover_por_matricula(turma, 20), ok_message, not_ok_message);
	print_lista(turma);
	print_error(remover_fim(turma), "Último aluno removido com sucesso!\n", "");
	print_lista(turma);
	print_error(remover_meio(turma, 3), "Aluno na 4° posição removido com sucesso!\n", "");

	/* 💣 */
	printf("\n");
	destruir(turma);
	printf("Lista destruída!\n");
	print_lista(turma);
	free(turma);
}


void print_lista(Lista *lista)
{
	int i, n = tamanho(lista);
	struct aluno aluno;

	if (n == NULL_ERROR) {
		printf("Lista inexistente!\n");
	}

	for (i = 0; i < n; ++i) {
		acessar_por_indice(lista, i, &aluno);
		printf("Aluno [%d]: %s.\n", aluno.matricula, aluno.nome);
	}
}


void print_error(int flag, char ok_message[], char not_ok_message[])
{
	switch (flag) {
		case OK: printf("%s", ok_message); break;
		case NOT_OK: printf("%s", not_ok_message); break;
		case NULL_ERROR: printf(MENSAGEM_LISTA_INEXISTENTE); break;
		case EMPTY_ERROR: printf("Erro: Lista vazia!\n"); break;
		case INPUT_ERROR:
			printf("Erro de entrada: não é possível acessar um índice negativo na lista.\n");
	}
}


void print_vazia(Lista *lista)
{
	switch (vazia(lista)) {
		case OK: printf("A lista está vazia!\n"); break;
		case NOT_OK: printf("A lista não está vazia!\n"); break;
		case NULL_ERROR: printf("Lista nula!\n"); break;
	}
}


void acessar_e_imprimir(Lista *lista, struct aluno *aluno, int matricula)
{
	int out;
	printf("\nAcessando aluno de matrícula número %d:\n", matricula);
	print_error(
		out = acessar_por_matricula(lista, 10, aluno), OK_MESSAGE_ACCESS, NOT_OK_MESSAGE_ACCESS);

	if (out == OK)
		printf("Aluno [%d]: %s.", aluno->matricula, aluno->nome);
}


/* Testa cada uma das funções definidas no TAD. Esvazia a lista no final da execução. */
void test_sample(Lista *lista)
{
	int i;
	char NOT_OK_MESSAGE_INSERTION[] = "Não foi possível inserir aluno na lista.\n";
	char OK_MESSAGE_REMOVAL[] = "Aluno removido com sucesso!\n";
	char NOT_OK_MESSAGE_REMOVAL[] = "Não foi possível remover aluno da lista!\n";
	struct aluno aluno = {.matricula = 0, .nome = "<teste>"};
	struct aluno cache = {.matricula = 0, .nome = "---"};

	printf("\n" LINE " Testes " LINE "\n");
	print_lista(lista);

	if ((i = tamanho(lista)) != NULL_ERROR)
		printf("Lista de tamanho: %d.\n", i);
	else
		printf("Lista inexistente!\n");

	/* Sucesso com uma lista quaisquer, que não seja nula. */
	printf("\nInserindo aluno no início da lista:\n");
	print_error(inserir_inicio(lista, aluno), MENSAGEM_INSERÇÃO_SUCESSO, NOT_OK_MESSAGE_INSERTION);
	print_error(acessar_por_indice(lista, 0, &cache), OK_MESSAGE_ACCESS, NOT_OK_MESSAGE_ACCESS);
	printf("Aluno [%d]: %s.\n", cache.matricula, cache.nome);

	print_error(remover_inicio(lista), OK_MESSAGE_REMOVAL, NOT_OK_MESSAGE_REMOVAL);
	printf("\nInserindo aluno no final da lista:\n");
	print_error(inserir_fim(lista, aluno), MENSAGEM_INSERÇÃO_SUCESSO, NOT_OK_MESSAGE_INSERTION);
	print_error(remover_fim(lista), OK_MESSAGE_REMOVAL, NOT_OK_MESSAGE_REMOVAL);

	/* Sucesso com uma lista de tamanho mínimo 2. */
	printf("\nInserindo aluno no meio da lista (2° posição):\n");
	print_error(inserir_meio(lista, aluno, 1), MENSAGEM_INSERÇÃO_SUCESSO, NOT_OK_MESSAGE_INSERTION);
	print_error(remover_meio(lista, 1), OK_MESSAGE_REMOVAL, NOT_OK_MESSAGE_REMOVAL);

	/* Deve ter um elemento com matrícula 10. */
	acessar_e_imprimir(lista, &cache, 10);
	print_error(remover_por_matricula(lista, 1), OK_MESSAGE_REMOVAL, NOT_OK_MESSAGE_REMOVAL);

	/* Deve ter um elemento com matrícula -10. */
	acessar_e_imprimir(lista, &cache, -10);
	print_error(remover_por_matricula(lista, -10), OK_MESSAGE_REMOVAL, NOT_OK_MESSAGE_REMOVAL);

	/* Erros de entradas negativas: */
	printf("\nInserindo aluno no índice -1:\n");
	print_error(
		inserir_meio(lista, aluno, -1), MENSAGEM_INSERÇÃO_SUCESSO, NOT_OK_MESSAGE_INSERTION);
	print_error(acessar_por_indice(lista, -1, &cache), OK_MESSAGE_ACCESS, NOT_OK_MESSAGE_ACCESS);
	printf("Aluno [%d]: %s.\n", cache.matricula, cache.nome);
	print_error(remover_meio(lista, -1), OK_MESSAGE_REMOVAL, NOT_OK_MESSAGE_REMOVAL);

	/* Esvaziar e limpar a lista */
	printf("\nEsvaziando a lista:\n");
	print_vazia(lista);
	destruir(lista);
	print_vazia(lista);
	free(lista);
}
