#include "locales.h"
#include <locale.h>
#include <string.h>

#define INEXISTENT_LIST_MESSAGE "Error: Inexistent list!\n"
#define MENSAGEM_LISTA_INEXISTENTE "Erro: Lista inexistente!\n"

#define INSERT_SUCCESS_MESSAGE "Successfully insert student!\n"
#define MENSAGEM_INSERÇÃO_SUCESSO "Aluno inserido com sucesso!\n"

#define OK_ACCESS_MESSAGE "Successfully access!\n"
#define MENSAGEM_ACESSO_SUCESSO "Acesso realizado com sucesso!\n"

#define NOT_OK_ACCESS_MESSAGE "Was not possible to complete access!\n"
#define MENSAGEM_ACESSO_SEM_SUCESSO "Não foi possível completar o acesso!\n"

#define ERROR_EMPTY_LIST_MESSAGE "Error: Empty list!\n"
#define MENSAGEM_ERRO_LISTA_VAZIA "Erro: Lista vazia!\n"

#define INPUT_ERROR_NEGATIVE_INDEX_MESSAGE \
		"Input error: it is not possible to access negative index from list.\n"
#define MENSAGEM_ERRO_ENTRADA_ÍNDICE_NEGATIVO \
		"Erro de entrada: não é possível acessar um índice negativo na lista.\n"

#define LIST_EMPTY_MESSAGE "The list is empty!\n"
#define MENSAGEM_LISTA_VAZIA "A lista está vazia!\n"

#define LIST_NOT_EMPTY_MESSAGE "The list is not empty!\n"
#define MENSAGEM_LISTA_NÃO_VAZIA "A lista não está vazia!\n"

#define NULL_LIST_MESSAGE "Null list!\n"
#define MENSAGEM_LISTA_NULA "Lista nula!\n"

#define CLEAR_LIST_MESSAGE "\nClear list:\n"
#define MENSAGEM_ESVAZIAR_LISTA "\nEsvaziar lista:\n"

#define STUDENT_MESSAGE "Student";
#define MENSAGEM_ALUNO "Aluno";

#define ACCESS_STUDENT_MESSAGE "Access student of registration number"
#define MENSAGEM_ACESSO_ESTUDANTE "Acessando student de matrícula número"

#define NO_MEMORY_ERROR_MESSAGE "Insufficient memory!\n"
#define MENSAGEM_ERRO_SEM_MEMÓRIA "Memória insuficiente!\n"

#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__))
// #include <unistd.h>
/* You can find out the version with _POSIX_VERSION.
..
..  */
#define GET_LOC() setlocale(LC_CTYPE, NULL)
// #elif defined(_WIN32)
// #include <Windows.h>
#else
GET_LOC() "Portuguese"
#endif

const char *inexistent_list_message;
const char *insert_success_message;
const char *ok_access_message;
const char *not_ok_access_message;
const char *error_empty_list_message;
const char *input_error_negative_index_message;
const char *list_empty_message;
const char *list_not_empty_message;
const char *null_list_message;
const char *clear_list_message;
const char *student_message;
const char *access_student_message;

const char *no_memory_error_message;

enum LOC loc;

void load_locales(enum LOC def)
{
    const char *locale = GET_LOC();

	if (def == EN || def != DEF && strcmp(locale, "English") == 0) {
		setlocale(LC_ALL, "English");
        inexistent_list_message = INEXISTENT_LIST_MESSAGE;
		insert_success_message = INSERT_SUCCESS_MESSAGE;
		ok_access_message = OK_ACCESS_MESSAGE;
		not_ok_access_message = NOT_OK_ACCESS_MESSAGE;
		error_empty_list_message = ERROR_EMPTY_LIST_MESSAGE;
		input_error_negative_index_message = INPUT_ERROR_NEGATIVE_INDEX_MESSAGE;
		list_empty_message = LIST_EMPTY_MESSAGE;
		list_not_empty_message = LIST_NOT_EMPTY_MESSAGE;
		null_list_message = NULL_LIST_MESSAGE;
		clear_list_message = CLEAR_LIST_MESSAGE;
		student_message = STUDENT_MESSAGE;
		access_student_message = ACCESS_STUDENT_MESSAGE;
		no_memory_error_message = NO_MEMORY_ERROR_MESSAGE;
		loc = EN;
	}
	else {
		setlocale(LC_ALL, "Portuguese");
		inexistent_list_message = MENSAGEM_LISTA_INEXISTENTE;
		insert_success_message = MENSAGEM_INSERÇÃO_SUCESSO;
		ok_access_message = MENSAGEM_ACESSO_SUCESSO;
		not_ok_access_message = MENSAGEM_ACESSO_SEM_SUCESSO;
		error_empty_list_message = MENSAGEM_ERRO_LISTA_VAZIA;
		input_error_negative_index_message = MENSAGEM_ERRO_ENTRADA_ÍNDICE_NEGATIVO;
		list_empty_message = MENSAGEM_LISTA_VAZIA;
		list_not_empty_message = MENSAGEM_LISTA_NÃO_VAZIA;
		null_list_message = MENSAGEM_LISTA_NULA;
		clear_list_message = MENSAGEM_ESVAZIAR_LISTA;
		student_message = MENSAGEM_ALUNO;
		access_student_message = MENSAGEM_ACESSO_ESTUDANTE;
		no_memory_error_message = MENSAGEM_ERRO_SEM_MEMÓRIA;
		loc = PT;
	}
}
