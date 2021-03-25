#include "input_validate.h"
#include "queue.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE "--------------------"
#define A_OR_B                                                                                     \
	input_boolean_choice("Escolha uma fila (A) (B):", "Aa", "Bb",                                  \
		"Entrada inválida, por favor, tente novamente",                                            \
		"Entrada vazia, por favor, tente novamente")

// clang-format off
#ifdef _WIN32
	#define CLEAR system("cls");
#elif __linux__
	#define CLEAR system("clear");
#elif __unix__
	#define CLEAR system("clear");
#else
	#define CLEAR ;
#endif

#ifdef _WIN32
	#define PAUSE system("pause");
#else
	#define PAUSE printf("Pressione enter para continuar..."); while (getchar() != '\n');
#endif
// clang-format on


/* Programa para testar a manipulação de filas, de forma manual ou automática. */
int main()
{
	void menu(void);
	void test(void);
	setlocale(LC_ALL, "Portuguese");

	while (1) {
		printf(LINE " Menu Principal " LINE "\n");
		printf("1 - Iniciar testes manuais\n");
		printf("2 - Iniciar testes automáticos\n");
		printf("0 - Sair\n");

		switch (input_integer_range(0, 2, ">>>", "Entrada inválida! Tente novamente",
			"Entrada vazia! Tente novamente", "Entrada inválida! Tente novamente")) {

			case 1: menu(); break;
			case 2: test(); break;
			default: return 0;
		}
	}

	return 0;
}


/* Menu do programa que permite manipular uma fila de estudantes. */
void menu()
{
	void print(Queue *);
	void remove_and_print(Queue *);
	void input_fill(Queue * queue, int *current_registration);
	void print_error(int flag, char ok_message[], char not_ok_message[]);

	Queue *queue_a, *queue_b;
	int registration_counter = 0;
	queue_a = queue_b = NULL;
	CLEAR

	while (1) {
		printf(LINE " Menu de testes " LINE "\n");
		int opt = 1;
		int not_a_is_empty = queue_size(queue_a) > 0;
		int b_is_empty = queue_size(queue_b) <= 0;
		int choices[] = {-1, -1, -1, -1, -1, -1, -1, -1};

		if (queue_a == NULL || queue_b == NULL) {
			printf("%d - Criar fila\n", opt);
			choices[0] = opt;
			++opt;
		}

		if (not_a_is_empty || !b_is_empty) {
			printf("%d - Esvaziar fila\n", opt);
			choices[1] = opt;
			++opt;
			printf("%d - Acessar aluno\n", opt);
			choices[2] = opt;
			++opt;
			printf("%d - Remover aluno da fila\n", opt);
			choices[3] = opt;
			++opt;
			printf("%d - Inverter fila\n", opt);
			choices[4] = opt;
			++opt;
		}

		if (not_a_is_empty && !b_is_empty) {
			printf("%d - Migrar fila (de B para A)\n", opt);
			choices[5] = opt;
			++opt;
		}

		if (queue_a != NULL || queue_b != NULL) {
			printf("%d - Adicionar alunos na fila\n", opt);
			choices[6] = opt;
			++opt;
			printf("%d - Ver fila\n", opt);
			choices[7] = opt;
		}

		printf("0 - Sair\n");

		int choice = input_integer_range(0, opt, ">>>", "Entrada inválida! Tente novamente",
			"Entrada vazia! Tente novamente", "Entrada inválida! Tente novamente");

		if (choice == (choices[0])) {
			// Criar fila
			if (queue_a == NULL) {
				queue_a = new_queue();
				printf("A ");
				print(queue_a);
			}
			else {
				queue_b = new_queue();
				printf("B ");
				print(queue_a);
			}
		}
		else if (choice == choices[1]) {
			// Esvaziar fila
			int a_or_b;

			if (not_a_is_empty && !b_is_empty)
				a_or_b = A_OR_B;
			else
				a_or_b = not_a_is_empty;

			if (a_or_b) {
				empty_queue(queue_a);
				printf("A ");
				print(queue_a);
			}
			else {
				empty_queue(queue_b);
				printf("B ");
				print(queue_b);
			}
		}
		else if (choice == choices[2]) {
			// Acessar aluno
			struct student student;
			int a_or_b;

			if (not_a_is_empty && !b_is_empty)
				a_or_b = A_OR_B;
			else
				a_or_b = not_a_is_empty;

			queue_get(a_or_b ? queue_a : queue_b, &student);
			printf("Aluno atual [%d] %s.\n", student.registration, student.name);
		}
		else if (choice == choices[3]) {
			// Remover aluno da fila
			int a_or_b;

			if (not_a_is_empty && !b_is_empty)
				a_or_b = A_OR_B;
			else
				a_or_b = not_a_is_empty;

			remove_and_print(a_or_b ? queue_a : queue_b);
		}
		else if (choice == choices[4]) {
			// Inverter fila
			int a_or_b;

			if (not_a_is_empty && !b_is_empty)
				a_or_b = A_OR_B;
			else
				a_or_b = not_a_is_empty;

			Queue *choosen_queue = a_or_b ? queue_a : queue_b;
			printf("Antes: ");
			print(choosen_queue);
			print_error(invert_queue(choosen_queue), "", "Erro ao inverter fila!\n");
			printf("Depois:");
			print(choosen_queue);
		}
		else if (choice == choices[5]) {
			// Migrar fila de B para A
			print_error(migrate_queue(queue_a, queue_b), "Fila migrada com sucesso!\n", "");
			printf("A ");
			print(queue_a);
			printf("B: ");
			print(queue_b);
		}
		else if (choice == choices[6]) {
			// Adicionar alunos
			if (queue_b == NULL)
				input_fill(queue_a, &registration_counter);
			else
				input_fill((A_OR_B ? queue_a : queue_b), &registration_counter);
		}
		else if (choice == choices[7]) {
			// Ver fila

			if (queue_b == NULL)
				print(queue_a);
			else
				print((A_OR_B ? queue_a : queue_b));
		}
		else {
			CLEAR
			break;
		}
		PAUSE
		CLEAR
	}

	if (queue_a != NULL)
		free(queue_a);

	if (queue_b != NULL)
		free(queue_b);

	int invert_queue(Queue *);
}


/* Imprime a fila, e o seu tamanho. */
void print(Queue *queue)
{
	if (print_queue(queue) != NULL_ERROR)
		printf(": tamanho %d.\n", queue_size(queue));
	else
		printf("Fila inexistente!\n");
}


/* Inicializa testes automáticos. */
void test()
{
	void test_sample(Queue *);
	void fill_queue(Queue *, char names[][NAME_MAX_SIZE], int size);
	void test_migration(char sample_names[][NAME_MAX_SIZE], char sample_size);

	int i;
	char names[][NAME_MAX_SIZE] = {"Roberto", "Dumont", "Pedro", "Gerson"};
	Queue *queue_a, *queue_b;
	CLEAR
	test_sample(NULL);

	for (i = 0; i <= 4; ++i) {
		queue_a = new_queue();
		fill_queue(queue_a, names, i);
		test_sample(queue_a);
	}
	for (i = -1; i <= 2; ++i)
		test_migration(names, i);

	PAUSE
	CLEAR
}


/* Imprime mensagens de erro conforme as flags obtidas de uma fila. */
void print_error(int flag, char ok_message[], char not_ok_message[])
{
	switch (flag) {
		case OK: printf("%s", ok_message); break;
		case NOT_OK: printf("%s", not_ok_message); break;
		case NULL_ERROR: printf("Erro: Fila inexistente!\n"); break;
		case EMPTY_ERROR: printf("Erro: Fila vazia!\n"); break;
	}
}


/* Remove um aluno da fila, e imprime o resultado. */
void remove_and_print(Queue *queue)
{
	struct student student;
	queue_get(queue, &student);

	printf("Removendo aluno [%d] %s.\n", student.registration, student.name);
	print_error(remove_from_queue(queue), "Aluno removido com sucesso!\n",
		"Não foi possível remover aluno da fila!\n");
	print(queue);
}


/* Recebe a entrada de novos alunos em uma fila. */
void input_fill(Queue *queue, int *current_registration)
{
	int n, i, all_ok;
	struct student student;
	n = input_min_integer(0, "Quantos alunos deseja adicionar à fila?",
		"Entrada inválida! Tente novamente", "Entrada vazia! Tente novamente",
		"Entrada negativa! Tente novamente:");

	for (i = 0; i < n; ++i) {
		printf("%d - Nome >>> ", i + 1);
		scanf("%s", student.name);
		student.registration = *current_registration;
		(*current_registration)++;

		if (!add_to_queue(queue, student)) {
			all_ok = FALSE;
			break;
		}
	}
	while ((char)getchar() != '\n') {
	}

	if (!all_ok)
		printf("Erro ao inserir alunos na fila\n");

	print(queue);
}


/* Preenche uma fila de alunos com os nomes passados. */
void fill_queue(Queue *queue, char names[][NAME_MAX_SIZE], int size)
{
	int i, all_ok = 1;
	struct student student;

	for (i = 0; i < size; ++i) {
		student.registration = 10 * (i + 1);
		strcpy(student.name, names[i]);

		if (add_to_queue(queue, student) != OK) {
			all_ok = 0;
			break;
		}
	}

	if (!all_ok)
		printf("Não foi possível preencher a fila!");
}


/* Imprime se a fila é vazia ou não, ou se não existe. */
void print_is_empty(Queue *queue)
{
	switch (queue_size(queue)) {
		case NULL_ERROR: printf("Fila nula!\n"); break;
		case 0: printf("A fila está vazia!\n"); break;
		default: printf("A fila não está vazia!\n"); break;
	}
}


/* Testa cada uma das funções definidas no TAD para uma determinada fila.
Esvazia a fila no final da execução. */
void test_sample(Queue *queue)
{
	int i;
	struct student student = {.registration = 0, .name = "<teste>"};
	struct student cache = {.registration = 0, .name = "---"};

	printf("\n" LINE " Testes " LINE "\n");

	switch (queue_get(queue, &cache)) {
		case OK:
			printf("Fila de tamanho %d. Aluno atual: [%d] "
				   "%s.\n",
				queue_size(queue), cache.registration, cache.name);
			break;
		case EMPTY_ERROR:
			printf("Fila vazia (de tamanho 0). Nenhum aluno "
				   "na fila!\n");
			break;
		case NULL_ERROR: printf("Fila inexistente!\n"); break;
	}

	print(queue);

	/* Sucesso com uma fila quaisquer, que não seja nula. */
	printf("\nInserindo aluno [%d: %s] no final da fila:\n", student.registration, student.name);
	print_error(add_to_queue(queue, student), "Aluno inserido com sucesso!\n",
		"Não foi possível inserir aluno na fila.\n");

	print(queue);

	printf("\nRemovendo aluno do início da fila:\n");
	print_error(remove_from_queue(queue), "Aluno removido com sucesso!\n",
		"Não foi possível remover aluno da fila!\n");
	print(queue);

	printf("\nInvertendo a ordem da fila:\n");
	print_error(invert_queue(queue), "Fila invertida com sucesso!\n", "");
	print(queue);

	/* Esvaziar e limpar a fila */
	printf("\nEsvaziando a fila:\n");

	printf("Antes: ");
	print_is_empty(queue);

	printf("Depois: ");
	empty_queue(queue);
	print_is_empty(queue);

	print(queue);
	free(queue);
}


/* Testa a função de 'migrar fila' do TAD, com diferentes tamanhos de filas. */
void test_migration(char sample_names[][NAME_MAX_SIZE], char sample_size)
{
	char names_b[][NAME_MAX_SIZE] = {"Marx", "Ju"};
	int j;

	for (j = -1; j <= 2; ++j) {
		Queue *class_a = NULL;
		Queue *class_b = NULL;

		printf(LINE " Migrando a fila A para B: " LINE "\n");

		if (sample_size >= 0) {
			class_a = new_queue();
			fill_queue(class_a, sample_names, sample_size);
		}
		printf("A: ");
		print(class_a);

		if (j >= 0) {
			class_b = new_queue();
			fill_queue(class_b, names_b, j);
		}
		printf("\nB: ");
		print(class_b);
		printf("\n");

		/* Migrar fila B para A. Gera um "barbequeu" :P */
		print_error(migrate_queue(class_a, class_b), "Fila migrada com sucesso!\n", "");
		printf("A: ");
		print(class_a);
		printf("\nB: ");
		print(class_b);
		printf("\n");

		empty_queue(class_a);
		empty_queue(class_b);

		if (class_a != NULL)
			free(class_a);

		if (class_b != NULL)
			free(class_b);
	}
}
