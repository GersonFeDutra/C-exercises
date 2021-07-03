#include "fila.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE "--------------------"


int main()
{
	setlocale(LC_ALL, "Portuguese");

	Fila *turma = criar();

	void test_sample(Fila *);
	void preencher_fila(Fila * turma, char nomes[][8], int size);
	int i;
	char nomes[][8] = {"Roberto", "Dumont", "Pedro"};

	test_sample(NULL);

	for (i = 1; i < 3; ++i) {

		preencher_fila(turma, nomes, i);
		test_sample(turma);
		turma = criar();
	}

	return 0;
}


/* Preenche uma fila de alunos com os nomes passados. */
void preencher_fila(Fila *fila, char nomes[][8], int size)
{
	int i, all_ok = 1;
	struct aluno aluno;

	for (i = 0; i < size; ++i) {
		aluno.matricula = 10 * (i + 1);
		strcpy(aluno.nome, nomes[i]);

		if (inserir(fila, aluno) != OK) {
			all_ok = 0;
			break;
		}
	}

	if (!all_ok)
		printf("Não foi possível preencher a fila!");
}


void print_fila(Fila *fila)
{
	struct aluno aluno;

	switch (acessar(fila, &aluno)) {
		case OK:
			printf("Fila de tamanho %d. Aluno atual: [%d] %s.\n", tamanho(fila), aluno.matricula,
				aluno.nome);
			break;
		case EMPTY_ERROR: printf("Fila vazia (de tamanho 0). Nenhum aluno na fila!\n"); break;
		case NULL_ERROR: printf("Fila inexistente!\n"); break;
	}
}


void print_error(int flag, char ok_message[], char not_ok_message[])
{
	switch (flag) {
		case OK: printf("%s", ok_message); break;
		case NOT_OK: printf("%s", not_ok_message); break;
		case NULL_ERROR: printf("Erro: Fila inexistente!\n"); break;
		case EMPTY_ERROR: printf("Erro: Fila vazia!\n"); break;
	}
}


void print_vazia(Fila *fila)
{
	switch (tamanho(fila)) {
		case NULL_ERROR: printf("Fila nula!\n"); break;
		case 0: printf("A fila está vazia!\n"); break;
		default: printf("A fila não está vazia!\n"); break;
	}
}


/* Testa cada uma das funções definidas no TAD. Esvazia a fila no final da execução. */
void test_sample(Fila *fila)
{
	int i;
	struct aluno aluno = {.matricula = 0, .nome = "<teste>"};
	struct aluno cache = {.matricula = 0, .nome = "---"};

	printf("\n" LINE " Testes " LINE "\n");
	print_fila(fila);

	/* Sucesso com uma fila quaisquer, que não seja nula. */
	printf("\nInserindo aluno [%d: %s] no final da fila:\n", aluno.matricula, aluno.nome);
	print_error(inserir(fila, aluno), "Aluno inserido com sucesso!\n",
		"Não foi possível inserir aluno na fila.\n");
	print_fila(fila);

	printf("\nRemovendo aluno do início da fila:\n");
	print_error(remover(fila), "Aluno removido com sucesso!\n",
		"Não foi possível remover aluno da fila!\n");
	print_fila(fila);

	/* Esvaziar e limpar a fila */
	printf("\nEsvaziando a fila:\n");
	print_vazia(fila);
	destruir(fila);
	print_vazia(fila);
	print_fila(fila);
	free(fila);
}
