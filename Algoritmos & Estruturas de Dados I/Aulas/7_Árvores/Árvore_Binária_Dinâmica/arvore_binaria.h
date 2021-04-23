#define OK 1           /* Operação realizada com sucesso. */
#define NOT_OK 0       /* Operação não foi realizada. */
#define NULL_ERROR -1  /* Árvore inexistente. */
#define EMPTY_ERROR -2 /* Árvore vazia. */
#define INPUT_ERROR -3 /* Entrada inválida. */

/* Árvore Binária de Busca Dinâmica. */
typedef struct no *Arvore;

/* Dados que serão usados no TAD. `matricula` será usado como identificador dos nós dessa árvore. */
struct aluno {
	int matricula;
	char nome[125];
	float av1;
	float av2;
};

/* Protótipos */

/* Cria uma árvore vazia. */
Arvore *criar_arvore(void);

/* 'Destrói' uma árvore, esvaziando seu conteúdo. */
void limpar_arvore(Arvore *);

/* Funções próprias da Árvore Binária de Busca.
Regras especiais:
- Cada nó tem um valor associado, mesmo que possua vários dados
    - No nosso caso, será a matrícula do aluno.
    - Esse valor é chamado de *chave*.
- Não existem chaves repetidas.
- Temos à esquerda de cada nó apenas nós com chaves _inferiores_ e à direita de cada nó apenas nós
com chaves _superiores_.
*/

/* Insere um aluno na árvore. Note que, árvores inserem na raíz e em nós com um ou nenhum filho -
na direita se houver um identificador maior que o do pai ou na esquerda se for menor. Não pode haver
matrículas iguais. Tentar inserir uma duplicata resultará em erro de entrada. Retorno: NULL_ERROR,
INPUT_ERROR, NOT_OK, OK. */
int inserir_no(Arvore *, struct aluno);

/* Remove um nó da árvore.
Retorno: NULL_ERROR, EMPTY_ERROR, NOT_OK, OK. */
int remover_no(Arvore *, int matricula);

/* Acessa os dados de um nó.
Retorno: NULL_ERROR, EMPTY_ERROR, NOT_OK, OK. */
int acessar_no(Arvore *, int matricula, struct aluno *saida);

// Percorrer árvore.

// /* Imprimir triangulado. */
// int print_arvore(Arvore *);

/* Imprime os nós da árvore, de acordo com o tipo de ordenação:
- -1 - pré-ordem: imprime os elementos na ordem em que os nós são acessados;
-  0 - em-ordem: imprime os nós da esquerda primeiro;
-  1 - pós-ordem: imprime os nós de ambos os lados, antes de imprimir um nó pai.
Retorno: NULL_ERROR, NOT_OK (se a entrada for inválida), OK. */
int percorrer(Arvore *ab, int tipo);

// Operações extras.

/* Retorna o tamanho / profundidade da árvore. É equivalente à altura da raíz.
Se a árvore for nula, retorna `NULL_ERROR`, ao invés disso.
Note que, uma árvore vazia tem altura 0. */
int altura(Arvore *);

/* Retorna a distância de um nó até a folha mais distante. Note que, folhas tem altura 1.
Erros: NULL_ERROR, EMPTY_ERROR, se o nó não for encontrado retornará 0. */
int altura_no(Arvore *, int matricula);

/* Retorna a quantidade de nós da árvore.
Se a árvore não existir retorna `NULL_ERROR`, ao invés disso. */
int quantidade_nos(Arvore *);

/* Verifica se a árvore está vazia. Uma árvore é vazia se não possuir raíz.
Retorno booleano (se a árvore for inexistente retorna `NULL_ERROR`, ao invés disso). */
int vazia(Arvore *ab);
