#define OK 1
#define NOT_OK 0       /* Não foi possível completar a operação. */
#define NULL_ERROR -1  /* Fila Inexistente. */
#define EMPTY_ERROR -2 /* Fila Vazia. */
#define MAX 50         /* Tamanho máximo da fila. */

struct aluno {
	int matricula;
	char nome[50];
};

typedef struct fila Fila;

/* Cria uma fila vazia. */
Fila *criar();

/* Retorna a quantidade de elementos da fila.
Se a fila não existir retorna `NULL_ERROR`, ao invés disso. */
int tamanho(Fila *);

/* 'Destrói' uma fila, esvaziando seu conteúdo.
Note que o ponteiro da fila continua existindo. */
void destruir(Fila *);

/* Insere um elemento. Note que, filas só podem inserir no final.
Retorno: NULL_ERROR, NOT_OK, OK. */
int inserir(Fila *, struct aluno);

/* Remove um elemento. Note que, filas só podem remover do início.
Retorno: NULL_ERROR, EMPTY_ERROR, OK. */
int remover(Fila *);

/* Acessa um elemento, sendo esse o primeiro elemento da fila.
Retorno: NULL_ERROR, EMPTY_ERROR, OK. */
int acessar(Fila *, struct aluno *);
