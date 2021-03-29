#define OK 1           /* Operação realizada com sucesso. */
#define NOT_OK 0       /* Operação não foi realizada. */
#define NULL_ERROR -1  /* Pilha inexistente. */
#define EMPTY_ERROR -2 /* Pilha vazia. */

// Pilha Dinâmica Heterogénea.
typedef struct elemento *Pilha;

// Dados que serão usados na pilha.
struct aluno {
	int matricula;
	char nome[100];
	// float av1;
	// float av2;
	// float pr;
};


/* Protótipos */

/* Cria uma pilha vazia. */
Pilha *criar();
/* `Pilha` é um nó descritor `struct pilha` que armazena dados de acesso aos elementos da pilha
(o elemento inicial e o elemento final). */

/* 'Destrói' uma pilha, esvaziando seu conteúdo. */
void destruir(Pilha *);

/* Retorna a quantidade de elementos da pilha.
Se a pilha não existir retorna `NULL_ERROR`, ao invés disso. */
int tamanho(Pilha *);

/* Insere um elemento. Note que, pilhas só podem inserir no final.
Retorno: NULL_ERROR, NOT_OK, OK. */
int inserir(Pilha *, struct aluno);

/* Remove um elemento. Note que, pilhas só podem remover do início.
Retorno: NULL_ERROR, EMPTY_ERROR, OK. */
int remover(Pilha *);

/* Acessa um elemento, sendo esse o primeiro elemento da pilha.
Retorno: NULL_ERROR, EMPTY_ERROR, OK. */
int acessar(Pilha *, struct aluno *);
