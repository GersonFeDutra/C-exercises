#include "pilha.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE "--------------------"


int main()
{
	setlocale(LC_ALL, "Portuguese");

	Pilha *turma = criar();

	void test_sample(Pilha *);
	void preencher_pilha(Pilha * turma, char nomes[][8], int size);
	int i;
	char nomes[][8] = {"Roberto", "Dumont", "Pedro"};

	test_sample(NULL);

	for (i = 0; i < 3; ++i) {

		preencher_pilha(turma, nomes, i);
		test_sample(turma);
		turma = criar();
	}

	return 0;
}

/* Preenche uma pilha de alunos com os nomes passados. */
void preencher_pilha(Pilha *pilha, char nomes[][8], int size)
{
	int i, all_ok = 1;
	struct aluno aluno;

	for (i = 0; i < size; ++i) {
		aluno.matricula = 10 * (i + 1);
		strcpy(aluno.nome, nomes[i]);

		if (inserir(pilha, aluno) != OK) {
			all_ok = 0;
			break;
		}
	}

	if (!all_ok)
		printf("Não foi possível preencher a pilha!");
}


void print_pilha(Pilha *pilha)
{
	struct aluno aluno;

	switch (acessar(pilha, &aluno)) {
		case OK:
			printf("Pilha de tamanho %d. Aluno atual: [%d] %s.\n", tamanho(pilha), aluno.matricula,
				aluno.nome);
			break;
		case EMPTY_ERROR: printf("Pilha vazia (de tamanho 0). Nenhum aluno na pilha!\n"); break;
		case NULL_ERROR: printf("Pilha inexistente!\n"); break;
	}
}


void print_error(int flag, char ok_message[], char not_ok_message[])
{
	switch (flag) {
		case OK: printf("%s", ok_message); break;
		case NOT_OK: printf("%s", not_ok_message); break;
		case NULL_ERROR: printf("Erro: Pilha inexistente!\n"); break;
		case EMPTY_ERROR: printf("Erro: Pilha vazia!\n"); break;
	}
}


void print_vazia(Pilha *pilha)
{
	switch (tamanho(pilha)) {
		case NULL_ERROR: printf("Pilha nula!\n"); break;
		case 0: printf("A pilha está vazia!\n"); break;
		default: printf("A pilha não está vazia!\n"); break;
	}
}


/* Testa cada uma das funções definidas no TAD. Esvazia a pilha no final da execução. */
void test_sample(Pilha *pilha)
{
	int i;
	struct aluno aluno = {.matricula = 0, .nome = "<teste>"};
	struct aluno cache = {.matricula = 0, .nome = "---"};

	printf("\n" LINE " Testes " LINE "\n");
	print_pilha(pilha);

	/* Sucesso com uma pilha quaisquer, que não seja nula. */
	printf("\nInserindo aluno [%d: %s] no topo da pilha:\n", aluno.matricula, aluno.nome);
	print_error(inserir(pilha, aluno), "Aluno inserido com sucesso!\n",
		"Não foi possível inserir aluno na pilha.\n");
	print_pilha(pilha);

	printf("\nRemovendo aluno do topo da pilha:\n");
	print_error(remover(pilha), "Aluno removido com sucesso!\n",
		"Não foi possível remover aluno da pilha!\n");
	print_pilha(pilha);

	/* Esvaziar e limpar a pilha */
	printf("\nEsvaziando a pilha:\n");
	print_vazia(pilha);
	destruir(pilha);
	print_vazia(pilha);
	print_pilha(pilha);
	free(pilha);
}
