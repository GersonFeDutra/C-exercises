#define OK 1           /* Operação realizada com sucesso. */
#define NOT_OK 0       /* Operação não foi realizada. */
#define NULL_ERROR -1  /* Árvore inexistente. */
#define EMPTY_ERROR -2 /* Árvore vazia. */
#define INPUT_ERROR -3 /* Entrada inválida. */

/* Árvore Binária de Busca Dinâmica. */
typedef struct node *Tree;

/* Dados que serão usados no TAD. `id` será usado como identificador dos nós dessa árvore. */
struct student {
	int id;
	char name[125];
	float av1;
	float av2;
};

/* Protótipos */

/* Cria uma árvore vazia. */
Tree *new_tree(void);

/* 'Destrói' uma árvore, esvaziando seu conteúdo. */
void clear_tree(Tree *);

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
int insert_node(Tree *, struct student);

/* Remove um nó da árvore.
Retorno: NULL_ERROR, EMPTY_ERROR, NOT_OK, OK. */
int remove_node(Tree *, int id);

/* Acessa os dados de um nó.
Retorno: NULL_ERROR, EMPTY_ERROR, NOT_OK, OK. */
int get_node(Tree *, int id, struct student *out);

// Percorrer árvore.

// /* Imprimir triangulado. */
// int print_tree(Tree *);

/* Imprime os nós da árvore, de acordo com o tipo de ordenação:
- -1 - pré-ordem: imprime os elementos na ordem em que os nós são acessados;
-  0 - em-ordem: imprime os nós da esquerda primeiro;
-  1 - pós-ordem: imprime os nós de ambos os lados, antes de imprimir um nó pai.
Retorno: NULL_ERROR, NOT_OK (se a entrada for inválida), OK. */
int travel_tree(Tree *bt, int type);

// Operações extras.

/* Retorna o tamanho / profundidade da árvore. É equivalente à altura da raíz.
Se a árvore for nula, retorna `NULL_ERROR`, ao invés disso.
Note que, uma árvore vazia tem altura 0. */
int tree_depth(Tree *);

/* Retorna a distância de um nó até a folha mais distante. Note que, folhas tem altura 1.
Erros: NULL_ERROR, EMPTY_ERROR, se o nó não for encontrado retornará 0. */
int node_depth(Tree *, int id);

/* Retorna a quantidade de nós da árvore.
Se a árvore não existir retorna `NULL_ERROR`, ao invés disso. */
int node_count(Tree *);

/* Verifica se a árvore está vazia. Uma árvore é vazia se não possuir raíz.
Retorno booleano (se a árvore for inexistente retorna `NULL_ERROR`, ao invés disso). */
int is_empty_tree(Tree *bt);

/* Acessa o nó com o maior identificador na árvore.
Note que o maior sempre será o último nó mais à direita na árvore.
Retorno: NULL_ERROR, EMPTY_ERROR, OK. */
int get_tree_higher_node(Tree *, struct student *out);

/* Retorna a quantidade de folhas da árvore. - Uma folha é um nó que não possui filhos.
Se a árvore não existir retorna `NULL_ERROR`, ao invés disso. */
int leaves_count(Tree *);

/* Acessa o nó com o menor identificador na árvore, restrito por um valor mínimo.
Note que o menor sempre será o último nó mais à esquerda na árvore - a aplicação da restrição
deslocará esse valor: o valor será maior ou igual a esse mínimo.
Retorno: NULL_ERROR, EMPTY_ERROR, NOT_OK, OK. */
int get_tree_nearest_lower(Tree *, int min, struct student *out);

/* Acessa o aluno com o n-ésimo menor identificador na pilha.
Retorno: NULL_ERROR, EMPTY_ERROR, INPUT_ERROR, NOT_OK, OK. */
int get_tree_nth_lower(Tree *bt, int n, struct student *out);

