#define OK 1           /* Operação realizada com sucesso. */
#define NOT_OK 0       /* Operação não foi realizada. */
#define NULL_ERROR -1  /* Lista inexistente. */
#define EMPTY_ERROR -2 /* Lista vazia. */
#define INPUT_ERROR -3 /* Entrada inválida. */

// Lista Dinâmica Simplesmente Encadeada Heterogénea.
typedef struct elemento *Lista;
/* Usamos `typedef` para definir o tipo de dado e ocultar o `*` da lista */

struct aluno {
	int matricula;
	char nome[100];
};

/* Protótipos */

/* Cria uma lista vazia. */
Lista *criar(void);
/* Lista é um `struct elemento *` que passaremos por referência: `Lista *`; isto é, `struct elemento
**`. Isso permite que o ponteiro inicial da lista seja alterado internamente nas funções. */

/* 'Destrói' uma lista, esvaziando o seu conteúdo. */
void destruir(Lista *);

/* Retorna a quantidade de elementos da lista.
Se a lista não existir retorna `NULL_ERROR`, ao invés disso. */
int tamanho(Lista *);

/* Insere um elemento no início da lista.
Retorno: NULL_ERROR, NOT_OK, OK. */
int inserir_inicio(Lista *, struct aluno);

/* Insere um elemento no final da lista.
Retorno: NULL_ERROR, NOT_OK, OK. */
int inserir_fim(Lista *, struct aluno);

/* Insere um elemento de forma 'ordenada', relativo à posição dos elementos na lista.
Retorno: NULL_ERROR, INPUT_ERROR, NOT_OK, OK. */
int inserir_meio(Lista *, struct aluno, int);

/* Remove o primeiro elemento da lista.
Retorno: NULL_ERROR, EMPTY_ERROR, OK */
int remover_inicio(Lista *);

/* Remove o último elemento da lista.
Retorno: NULL_ERROR, EMPTY_ERROR, OK. */
int remover_fim(Lista *);

/* Remove um elemento de acordo com sua posição na lista.
Retorno: NULL_ERROR, EMPTY_ERROR, INPUT_ERROR, NOT_OK, OK. */
int remover_meio(Lista *, int);

/* Remove o elemento indicado da lista.
Retorno: NULL_ERROR, EMPTY_ERROR, NOT_OK, OK. */
int remover_por_matricula(Lista *, int matricula);

/* Acessa um elemento da lista por índice.
Retorno: NULL_ERROR, EMPTY_ERROR, INPUT_ERROR, NOT_OK, OK. */
int acessar_por_indice(Lista *, int, struct aluno *saida);

/* Acessa um elemento da matriz com busca (matrícula).
Retorno: NULL_ERROR, EMPTY_ERROR, NOT_OK, OK.*/
int acessar_por_matricula(Lista *, int matricula, struct aluno *saida);

/* Retorna `OK` se a lista estiver vazia, e `NOT_OK`, caso contrário.
Também retorna `NULL_ERROR`, se a lista for inexistente */
int vazia(Lista *);

// int cheia(Lista *); // Por ser uma lista dinâmica ela não pode ficar cheia.
