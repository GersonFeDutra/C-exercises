#include "list.h"
#include "locales.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[])
{
	enum LOC def = DEF;
	
	while (argc-- > 1)
		if (*(*++argv)++ == '-') {
			if (strcmp(*argv, "en") == 0)
				def = EN;
			else if (strcmp(*argv, "pt"))
				def = PT;
		}
	load_locales(def);

	List *classmates = list_create();
	// printf("List não existe.\n");
	// printf("List vazia!\n");

	void test_sample(List *);
	void fill_list(List * classmates, char names[][8], int size);
	int i;
	char names[][8] = {"Roberto", "Dumont", "Pedro"};

	test_sample(NULL);

	for (i = 1; i < 3; ++i) {
		fill_list(classmates, names, i);
		test_sample(classmates);
		classmates = list_create();
	}

	void test(void);
	printf("\n");
	test();

	return 0;
}


/* Preenche uma lista de alunos com os nomes passados. */
void fill_list(List *classmates, char names[][8], int size)
{
	int i;
	struct student student;

	for (i = 0; i < size; ++i) {
		student.registry = 10 * (i + 1);
		strcpy(student.name, names[i]);

		if (list_insert_first(classmates, student) == NULL_ERROR)
			printf(inexistent_list_message);
	}
}


void test()
{
	void print_list(List *);
	void print_error(int flag, const char ok_message[], const char not_ok_message[]);
	const int ENTRIES = 4;

	int i;
	// Caches para concatenação de strings.
	char ok_message[160];
	char not_ok_message[160];
	char names[][8] = {"Roberto", "Dumont", "Pedro", "Gerson"};
	struct student student;
	List *classmates = list_create();
	
	const char *started_list_message;
	const char *operations_message;
	const char *first_student_message;
	const char *removed_successfully_message;
	const char *insertions_message;
	const char *insert_student_message;
	const char *registration_number_message;
	const char *end_of_list_message;
	const char *third_position_message;
	const char *destroyed_message;
	const char *remotions_message;
	const char *list_index_error_message;
	const char *index_successful_message;
	const char *index_error_message;
	const char *registry_not_found_message;
	const char *registry_access_message;
	const char *student_removed_message;
	const char *student_removed_at_message;
	const char *registry_student_message;
	const char *remove_success_message;
	const char *not_remove_registry_message;
	
	if (loc == EN) {
		static char STARTED_LIST_MESSAGE[] = "Started list";
		static char OPERATIONS_MESSAGE[] = "Operations";
		static char FIRST_STUDENT_MESSAGE[] = "First student";
		static char REMOVED_SUCCESSFULLY_MESSAGE[] = "Removed successfully";
		static char INSERTIONS_MESSAGE[] = "Insertions";
		static char INSERT_STUDENT_MESSAGE[] = "Insert student";
		static char REGISTRATION_NUMBER_MESSAGE[] = "with registration number";
		static char END_OF_LIST_MESSAGE[] = "at end of list";
		static char THIRD_POSITION_MESSAGE[] = "at third position";
		static char DESTROYED_MESSAGE[] = "Destroyed list!\n";
		static char REMOTIONS_MESSAGE[] = "Remotions";
		static char LIST_INDEX_ERROR_MESSAGE[] = "Error accessing index 7 from list.\n";
		static char INDEX_SUCCESSFUL_MESSAGE[] = "Index 2 access successful: ";
		static char INDEX_ERROR_MESSAGE[] = "Index 2 access error!";
		static char REGISTRY_NOT_FOUND_MESSAGE[] = "Registry [70] not found.\n";
		static char REGISTRY_ACCESS_MESSAGE[] = "Registry number [30] successful access!\n";
		static char STUDENT_REMOVED_MESSAGE[] = "Last student removed success!\n";
		static char STUDENT_REMOVED_AT_MESSAGE[] = "Student at index 4° position remove success!\n";
		static char REGISTRY_STUDENT_MESSAGE[] = "Student with registry";
		static char REMOVE_SUCCESS_MESSAGE[] = "remove success";
		static char NOT_REMOVE_REGISTRY_MESSAGE[] = "Was not possible to remove registry";
		started_list_message = STARTED_LIST_MESSAGE;
		operations_message = OPERATIONS_MESSAGE;
		first_student_message = FIRST_STUDENT_MESSAGE;
		removed_successfully_message = REMOVED_SUCCESSFULLY_MESSAGE;
		insertions_message = INSERTIONS_MESSAGE;
		insert_student_message = INSERT_STUDENT_MESSAGE;
		registration_number_message = REGISTRATION_NUMBER_MESSAGE;
		end_of_list_message = END_OF_LIST_MESSAGE;
		third_position_message = THIRD_POSITION_MESSAGE;
		destroyed_message = DESTROYED_MESSAGE;
		remotions_message = REMOTIONS_MESSAGE;
		list_index_error_message = LIST_INDEX_ERROR_MESSAGE;
		index_successful_message = INDEX_SUCCESSFUL_MESSAGE;
		index_error_message = INDEX_ERROR_MESSAGE;
		registry_not_found_message = REGISTRY_NOT_FOUND_MESSAGE;
		registry_access_message = REGISTRY_ACCESS_MESSAGE;
		student_removed_message = STUDENT_REMOVED_MESSAGE;
		student_removed_at_message = STUDENT_REMOVED_AT_MESSAGE;
		registry_student_message = REGISTRY_STUDENT_MESSAGE;
		remove_success_message = REMOVE_SUCCESS_MESSAGE;
		not_remove_registry_message = NOT_REMOVE_REGISTRY_MESSAGE;
	}
	else {
		static char STARTED_LIST_MESSAGE[] = "Lista inicializada";
		static char OPERATIONS_MESSAGE[] = "Operações";
		static char FIRST_STUDENT_MESSAGE[] = "Primeiro aluno";
		static char REMOVED_SUCCESSFULLY_MESSAGE[] = "Removido com sucesso";
		static char INSERTIONS_MESSAGE[] = "Inserções";
		static char INSERT_STUDENT_MESSAGE[] = "Inserindo aluno";
		static char REGISTRATION_NUMBER_MESSAGE[] = "com matrícula de número";
		static char END_OF_LIST_MESSAGE[] = "no final da lista";
		static char THIRD_POSITION_MESSAGE[] = "na terceira posição";
		static char DESTROYED_MESSAGE[] = "Lista destruída!\n";
		static char REMOTIONS_MESSAGE[] = "Remoções";
		static char LIST_INDEX_ERROR_MESSAGE[] = "Erro ao acessar índice 7 da lista.\n";
		static char INDEX_SUCCESSFUL_MESSAGE[] = "Índice 2 acessado com sucesso: ";
		static char INDEX_ERROR_MESSAGE[] = "Erro ao acessar índice 2.\n";
		static char REGISTRY_NOT_FOUND_MESSAGE[] = "Matrícula [70] não foi encontrada.\n";
		static char REGISTRY_ACCESS_MESSAGE[] = "Matrícula de número [30] acessada com sucesso!\n";
		static char STUDENT_REMOVED_MESSAGE[] = "Último student removido com sucesso!\n";
		static char STUDENT_REMOVED_AT_MESSAGE[] = "Aluno na 4° posição removido com sucesso!\n";
		static char REGISTRY_STUDENT_MESSAGE[] = "Aluno de matrícula";
		static char REMOVE_SUCCESS_MESSAGE[] = "removido com sucesso";
		static char NOT_REMOVE_REGISTRY_MESSAGE[] = "Não foi possível remover matrícula";
		started_list_message = STARTED_LIST_MESSAGE;
		operations_message = OPERATIONS_MESSAGE;
		first_student_message = FIRST_STUDENT_MESSAGE;
		removed_successfully_message = REMOVED_SUCCESSFULLY_MESSAGE;
		insertions_message = INSERTIONS_MESSAGE;
		insert_student_message = INSERT_STUDENT_MESSAGE;
		end_of_list_message = END_OF_LIST_MESSAGE;
		third_position_message = THIRD_POSITION_MESSAGE;
		registration_number_message = REGISTRATION_NUMBER_MESSAGE;
		destroyed_message = DESTROYED_MESSAGE;
		remotions_message = REMOTIONS_MESSAGE;
		list_index_error_message = LIST_INDEX_ERROR_MESSAGE;
		index_successful_message = INDEX_SUCCESSFUL_MESSAGE;
		index_error_message = INDEX_ERROR_MESSAGE;
		registry_not_found_message = REGISTRY_NOT_FOUND_MESSAGE;
		registry_access_message = REGISTRY_ACCESS_MESSAGE;
		student_removed_message = STUDENT_REMOVED_MESSAGE;
		student_removed_at_message = STUDENT_REMOVED_AT_MESSAGE;
		registry_student_message = REGISTRY_STUDENT_MESSAGE;
		remove_success_message = REMOVE_SUCCESS_MESSAGE;
		not_remove_registry_message = NOT_REMOVE_REGISTRY_MESSAGE;
	}

	/* Coleta de dados */
	fill_list(classmates, names, ENTRIES);

	// Como a inserção foi realizada no início, "Gerson" deve ser o 1º nome e "Roberto" o último.
	printf(LINE " %s " LINE "\n", started_list_message);
	print_list(classmates);

	/* Operações */

	printf(LINE " %s " LINE "\n", operations_message);
	print_error(list_access_at_index(classmates, 0, &student), "", "");
	sprintf(ok_message, "%s [%s] %s!\n", first_student_message,
			student.name, removed_successfully_message);
	print_error(list_remove_first(classmates), ok_message, "");
	print_list(classmates);

	// Deve dar erro
	print_error(list_access_at_index(classmates, 7, &student), "", list_index_error_message);

	print_error(list_access_at_index(classmates, 7, &student), "", list_index_error_message);
	// Usei a atribuição na mesma linha da chamada `print_error()` só pq eu posso mesmo! :P
	print_error((i = list_access_at_index(classmates, -4, &student)), "", ""); // Deve dar erro

	print_error((i = list_access_at_index(classmates, 2, &student)),
		index_successful_message, index_error_message);

	if (i == OK)
		printf("(%d) %s\n", student.registry, student.name);

	print_error(list_access_registry(classmates, 70, &student),
			"", registry_not_found_message); // Deve dar erro
	print_error(list_access_registry(classmates, 30, &student),
		registry_access_message, ""); // Acessando registry 30
	printf("%s [%d] %s.\n", student_message, student.registry, student.name);

	/* Mais inserções */

	printf(LINE " %s " LINE "\n", insertions_message);

	strcpy(student.name, "Marx");
	student.registry = (ENTRIES + 1) * 10;
	printf("%s [%s], %s [%d], %s...\n",
		insert_student_message, student.name, registration_number_message,
		student.registry, end_of_list_message);
	print_error(list_insert_end(classmates, student), insert_success_message, "");
	print_list(classmates);

	strcpy(student.name, "Ju");
	student.registry = (ENTRIES + 2) * 10;
	printf("%s [%s] %s...\n", insert_student_message, student.name, third_position_message);
	print_error(list_insert_at(classmates, student, 2), insert_success_message, "");
	print_list(classmates);

	/* Remoções */

	printf(LINE " %s " LINE "\n", remotions_message);
	sprintf(ok_message, "%s [%d] %s.\n", registry_student_message, 20, remove_success_message);
	sprintf(not_ok_message, "%s [%d].\n", not_remove_registry_message, 20);
	print_error(list_remove_registry(classmates, 20), ok_message, not_ok_message);
	print_list(classmates);
	print_error(list_remove_end(classmates), student_removed_message, "");
	print_list(classmates);
	print_error(list_remove_at(classmates, 3), student_removed_at_message, "");

	/* 💣 */
	printf("\n");
	list_free(classmates);
	printf(destroyed_message);
	print_list(classmates);
	free(classmates);
}


void print_list(List *list)
{
	int i, n = list_size(list);
	struct student student;

	if (n == NULL_ERROR)
		printf(inexistent_list_message);

	for (i = 0; i < n; ++i) {
		list_access_at_index(list, i, &student);
		printf("%s [%d]: %s.\n", student_message, student.registry, student.name);
	}
}


void print_error(int flag, const char ok_message[], const char not_ok_message[])
{
	switch (flag) {
		case OK: printf("%s", ok_message); break;
		case NOT_OK: printf("%s", not_ok_message); break;
		case NULL_ERROR: printf(inexistent_list_message); break;
		case EMPTY_ERROR: printf(error_empty_list_message); break;
		case INPUT_ERROR: printf(input_error_negative_index_message); break;
	}
}


void print_vazia(List *list)
{
	switch (list_is_empty(list)) {
		case OK: printf(list_empty_message); break;
		case NOT_OK: printf(list_not_empty_message); break;
		case NULL_ERROR: printf(null_list_message); break;
	}
}


void acessar_e_imprimir(List *list, struct student *student, int registry)
{
	int out;
	printf("\n%s %d:\n", access_student_message, registry);
	print_error(out = \
			list_access_registry(list, 10, student),
			ok_access_message, not_ok_access_message);

	if (out == OK)
		printf("%s [%d]: %s.\n", student_message, student->registry, student->name);
}


/* Testa cada uma das funções definidas no TAD. Esvazia a lista no final da execução. */
void test_sample(List *list)
{
	int i;
	const char *not_ok_insert_message;
	const char *ok_remove_message;
	const char *not_ok_remove_message;
	const char *test_name;
	const char *insert_student_start_message;
	const char *tests_message;
	const char *list_size_message;
	const char *inexistent_list_message;
	const char *insert_student_end_message;
	const char *insert_student_mid_message;
	const char *insert_student_negative_index_message;

	if (loc == EN) {
		static char NOT_OK_MESSAGE_INSERTION[] = "Was not possible to insert student on list.\n";
		static char OK_MESSAGE_REMOVAL[] = "Student removed successfully!\n";
		static char NOT_OK_MESSAGE_REMOVAL[] = "Was not possible to remove student from list!\n";
		static char TEST_NAME[] = "<test>";
		static char INSERT_STUDENT_START_MESSAGE[] = "\nInserting student at list beginning:\n";
		static char TESTS[] = "Tests";
		static char LIST_SIZE_MESSAGE[] = "List of size";
		static char INEXISTENT_LIST_MESSAGE[] = "Inexistent list!\n";
		static char INSERT_STUDENT_END_MESSAGE[] = "\nInsert student at list end:\n";
		static char INSERT_STUDENT_MID_MESSAGE[] = "\nInsert student in list (2° position):\n";
		static char INSERT_STUDENT_NEGATIVE_INDEX_MESSAGE[] = "\nInsert student at index -1:\n";
		not_ok_insert_message = NOT_OK_MESSAGE_INSERTION;
		ok_remove_message = OK_MESSAGE_REMOVAL;
		not_ok_remove_message = NOT_OK_MESSAGE_REMOVAL;
		test_name = TEST_NAME;
		insert_student_start_message = INSERT_STUDENT_START_MESSAGE;
		tests_message = TESTS;
		list_size_message = LIST_SIZE_MESSAGE;
		inexistent_list_message = INEXISTENT_LIST_MESSAGE;
		insert_student_end_message = INSERT_STUDENT_END_MESSAGE;
		insert_student_mid_message = INSERT_STUDENT_MID_MESSAGE;
		insert_student_negative_index_message = INSERT_STUDENT_NEGATIVE_INDEX_MESSAGE;
	} else {
		static char NOT_OK_MESSAGE_INSERTION[] = "Não foi possível inserir aluno na lista.\n";
		static char OK_MESSAGE_REMOVAL[] = "Aluno removido com sucesso!\n";
		static char NOT_OK_MESSAGE_REMOVAL[] = "Não foi possível remover aluno da lista!\n";
		static char TEST_NAME[] = "<teste>";
		static char INSERT_STUDENT_START_MESSAGE[] = "\nInserindo aluno no início da lista:\n";
		static char TESTS[] = "Testes";
		static char LIST_SIZE_MESSAGE[] = "ListA de tamanho";
		static char INEXISTENT_LIST_MESSAGE[] = "ListA inexistente!\n";
		static char INSERT_STUDENT_END_MESSAGE[] = "\nInserindo aluno no final da lista:\n";
		static char INSERT_STUDENT_MID_MESSAGE[] = \
				"\nInserindo aluno no meio da lista (2° posição):\n";
		static char INSERT_STUDENT_NEGATIVE_INDEX_MESSAGE[] = "\nInserindo aluno no índice -1:\n";
		not_ok_insert_message = NOT_OK_MESSAGE_INSERTION;
		ok_remove_message = OK_MESSAGE_REMOVAL;
		not_ok_remove_message = NOT_OK_MESSAGE_REMOVAL;
		test_name = TEST_NAME;
		insert_student_start_message = INSERT_STUDENT_START_MESSAGE;
		tests_message = TESTS;
		list_size_message = LIST_SIZE_MESSAGE;
		inexistent_list_message = INEXISTENT_LIST_MESSAGE;
		insert_student_mid_message = INSERT_STUDENT_MID_MESSAGE;
		insert_student_negative_index_message = INSERT_STUDENT_NEGATIVE_INDEX_MESSAGE;
	}

	struct student student = { .registry = 0, };
	strcpy(student.name, test_name);
	struct student cache = {.registry = 0, .name = "---"};

	printf("\n" LINE " %s " LINE "\n", tests_message);
	print_list(list);

	if ((i = list_size(list)) != NULL_ERROR)
		printf("%s: %d.\n", list_size_message, i);
	else
		printf(inexistent_list_message);

	/* Sucesso com uma lista quaisquer, que não seja nula. */
	printf(insert_student_start_message);
	print_error(list_insert_first(list, student), insert_success_message, not_ok_insert_message);
	print_error(list_access_at_index(list, 0, &cache), ok_access_message, not_ok_access_message);
	printf("%s [%d]: %s.\n", student_message, cache.registry, cache.name);

	print_error(list_remove_first(list), ok_remove_message, not_ok_remove_message);
	printf(insert_student_end_message);
	print_error(list_insert_end(list, student), insert_success_message, not_ok_insert_message);
	print_error(list_remove_end(list), ok_remove_message, not_ok_remove_message);

	/* Sucesso com uma lista de tamanho mínimo 2. */
	printf(insert_student_mid_message);
	print_error(list_insert_at(list, student, 1), insert_success_message, not_ok_insert_message);
	print_error(list_remove_at(list, 1), ok_remove_message, not_ok_remove_message);

	/* Deve ter um elemento com matrícula 10. */
	acessar_e_imprimir(list, &cache, 10);
	print_error(list_remove_registry(list, 1), ok_remove_message, not_ok_remove_message);

	/* Deve ter um elemento com matrícula -10. */
	acessar_e_imprimir(list, &cache, -10);
	print_error(list_remove_registry(list, -10), ok_remove_message, not_ok_remove_message);

	/* Erros de entradas negativas: */
	printf(insert_student_negative_index_message);
	print_error(
		list_insert_at(list, student, -1), insert_success_message, not_ok_insert_message);
	print_error(list_access_at_index(list, -1, &cache), ok_access_message, not_ok_access_message);
	printf("%s [%d]: %s.\n", student_message, cache.registry, cache.name);
	print_error(list_remove_at(list, -1), ok_remove_message, not_ok_remove_message);

	/* Esvaziar e limpar a lista */
	printf(clear_list_message);
	print_vazia(list);
	list_free(list);
	print_vazia(list);
	free(list);
}
