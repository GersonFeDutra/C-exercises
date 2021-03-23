#define OK 1           /* Operação realizada com sucesso. */
#define NOT_OK 0       /* Operação não foi realizada. */
#define NULL_ERROR -1  /* Lista inexistente. */
#define EMPTY_ERROR -2 /* Lista vazia. */

// Fila Dinâmica Heterogénea.
typedef struct fila Fila;

// Dados que serão usados na fila.
struct aluno {
	int matricula;
	char nome[50];
};

/* Protótipos */

/* Cria uma fila vazia. */
Fila *criar();
/* `Fila` é um nó descritor `struct fila` que armazena dados de acesso aos elementos da fila
(o elemento inicial e o elemento final). */

/* 'Destrói' uma fila, esvaziando seu conteúdo. */
void destruir(Fila *);

/* Retorna a quantidade de elementos da fila.
Se a fila não existir retorna `NULL_ERROR`, ao invés disso. */
int tamanho();

/* Insere um elemento. Note que, filas só podem inserir no final.
Retorno: NULL_ERROR, NOT_OK, OK. */
int inserir(Fila *, struct aluno);

/* Remove um elemento. Note que, filas só podem remover do início.
Retorno: NULL_ERROR, EMPTY_ERROR, OK. */
int remover(Fila *);

/* Acessa um elemento, sendo esse o primeiro elemento da fila.
Retorno: NULL_ERROR, EMPTY_ERROR, OK. */
int acessar(Fila *, struct aluno *);
