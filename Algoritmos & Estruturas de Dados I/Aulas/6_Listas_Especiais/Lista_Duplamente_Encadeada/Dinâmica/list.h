#define OK 1           /* Operação realizada com sucesso. */
#define NOT_OK 0       /* Operação não foi realizada. */
#define NULL_ERROR -1  /* Lista inexistente. */
#define EMPTY_ERROR -2 /* Lista vazia. */
#define INPUT_ERROR -3 /* Entrada inválida. */

// Lista Dinâmica Duplamente Encadeada Heterogênea.
typedef struct element *List;
/* Usamos `typedef` para definir o tipo de dado e ocultar o `*` da lista */

struct student {
	int registry;
	char name[100];
};

/* Protótipos */

/* Cria uma lista vazia. */
List *list_create(void);
/* List é um `struct element *` que passaremos por referência: `List *`; isto é, `struct element
**`. Isso permite que o ponteiro inicial da lista seja alterado internamente nas funções. */

/* 'Destrói' uma lista, esvaziando o seu conteúdo. */
void list_free(List *);

/* Retorna a quantidade de elementos da lista.
Se a lista não existir retorna `NULL_ERROR`, ao invés disso. */
int list_size(List *);

/* Insere um elemento no início da lista.
Retorno: NULL_ERROR, NOT_OK, OK. */
int list_insert_first(List *, struct student);

/* Insere um elemento no final da lista.
Retorno: NULL_ERROR, NOT_OK, OK. */
int list_insert_end(List *, struct student);

/* Insere um elemento de forma 'ordenada',
relativo à posição dos elementos na lista.
Se o índice passado for negativo conta do último ao primeiro: O(n)=2n, Θ(n)=n
Retorno: NULL_ERROR, INPUT_ERROR, NOT_OK, OK. */
int list_insert_at(List *, struct student, int);

/* Remove o primeiro elemento da lista.
Retorno: NULL_ERROR, EMPTY_ERROR, OK */
int list_remove_first(List *);

/* Remove o último elemento da lista.
Retorno: NULL_ERROR, EMPTY_ERROR, OK. */
int list_remove_end(List *);

/* Remove um elemento de acordo com sua posição na lista.
Retorno: NULL_ERROR, EMPTY_ERROR, INPUT_ERROR, NOT_OK, OK. */
int list_remove_at(List *, int);

/* Remove o elemento indicado da lista.
Retorno: NULL_ERROR, EMPTY_ERROR, NOT_OK, OK. */
int list_remove_registry(List *, int registry);

/* Acessa um elemento da lista por índice.
Se o índice passado for negativo conta do último ao primeiro: O(n)=2n, Θ(n)=n
Retorno: NULL_ERROR, EMPTY_ERROR, INPUT_ERROR, NOT_OK, OK. */
int list_access_at_index(List *, int, struct student *out);

/* Acessa um elemento da matriz com busca (matrícula).
Retorno: NULL_ERROR, EMPTY_ERROR, NOT_OK, OK.*/
int list_access_registry(List *, int registry, struct student *out);

/* Retorna `OK` se a lista estiver vazia, e `NOT_OK`, caso contrário.
Também retorna `NULL_ERROR`, se a lista for inexistente */
int list_is_empty(List *);

// int cheia(List *); // Por ser uma lista dinâmica ela não pode ficar cheia.
