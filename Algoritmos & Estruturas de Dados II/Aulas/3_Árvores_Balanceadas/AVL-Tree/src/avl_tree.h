#include <inttypes.h>

#define OK 1           /* Operação realizada com sucesso. */
#define NOT_OK 0       /* Operação não foi realizada. */
#define NULL_ERROR -1  /* Árvore inexistente. */
#define EMPTY_ERROR -2 /* Árvore vazia. */
#define INPUT_ERROR -3 /* Entrada inválida. */

/* Árvore AVL (Árvore Binária de Busca Balanceada) Dinâmica. */
typedef struct node *Tree;
/* Essa árvore funciona de forma "dinâmica", ou seja, apenas armazena os endereços para os dados e
não os dados em si. Esses serão passados com um ponteiro genérico (do tipo void). */


/* Protótipos */

/* Cria uma árvore vazia. */
Tree *new_tree(void);

/* 'Destrói' uma árvore, esvaziando seu conteúdo.
 * Note que apenas as referências serão eliminadas, os dados continuarão existindo.
 */
// void clear_tree(Tree *);

/* 'Destrói' uma árvore, eliminando seu conteúdo (os dados serão eliminados da memória).
 */
void free_nodes(Tree *);

/* Funções próprias da Árvore Binária de Busca.
Regras especiais:
- Cada nó tem um valor associado, mesmo que possua vários dados;
    - Esse valor é chamado de *chave*.
    - Como essa é uma árvore de indexação o valor da chave é definido externamente por outros TADs
    que a usam.
- Não há chaves repetidas.
- Temos à esquerda de cada nó apenas nós com chaves _inferiores_ e à direita de cada nó apenas nós
com chaves _superiores_.
*/

/* Insere um elemento na árvore. Note que, árvores inserem na raíz, se a mesma for vazia, ou em nós
 * com um ou nenhum filho - na direita se houver um identificador maior que o do pai ou na esquerda
 * se for menor. Não pode haver chaves iguais. Tentar inserir uma duplicata resultará em erro de
 * entrada.
 * Retorno: `NULL_ERROR`, `INPUT_ERROR`, `NOT_OK`, `OK`.
 */
int8_t insert_node(Tree *, void *, int32_t key);

/* Remove um nó da árvore, retornando o seu conteúdo.
 * Retorno: `NULL_ERROR`, `EMPTY_ERROR`, `NOT_OK`, `OK`.
 */
// int8_t remove_node(Tree *avl_tree, int32_t key, void **r_element);

/* Remove um nó da árvore, liberando seu conteúdo da memória.
 * Retorno: `NULL_ERROR`, `EMPTY_ERROR`, `NOT_OK`, `OK`.
 */
int8_t free_node(Tree *avl_tree, int32_t key);


/* Acessa o índice (ponteiro `void` para dados definidos externamente) de um nó.
 * Retorno: `NULL_ERROR`, `EMPTY_ERROR`, `NOT_OK`, `OK`.
 */
int8_t get_node(Tree *avl_tree, int32_t key, void **r_element);

// Percorrer árvore.

// /* Imprimir triangulado. */
// int print_tree(Tree *);

/* Imprime os nós da árvore, de acordo com o tipo de ordenação:
 * - -1. pré-ordem: imprime os elementos na ordem em que os nós são acessados;
 * -  0. em-ordem: imprime os nós da esquerda primeiro;
 * -  1. pós-ordem: imprime os nós de ambos os lados, antes de imprimir um nó pai.
 * Retorno: `NULL_ERROR`, `NOT_OK` (se a entrada for inválida), `OK`.
 */
int8_t travel_tree(Tree *bt, int8_t type);

// Operações extras.

/* Retorna o tamanho / profundidade da árvore. É equivalente à altura da raíz.
 * Se a árvore for nula, retorna `NULL_ERROR`, ao invés disso.
 * Note que, uma árvore vazia tem altura 0.
 */
int tree_depth(Tree *);

/* Retorna a distância de um nó até a folha mais distante. Note que, folhas tem altura 1.
 * Erros: `NULL_ERROR`, `EMPTY_ERROR`, se o nó não for encontrado retornará 0.
 */
int32_t node_depth(Tree *, int id);

/* Retorna a quantidade de nós da árvore.
 * Se a árvore não existir retorna `NULL_ERROR`, ao invés disso.
 */
int32_t node_count(Tree *);

/* Verifica se a árvore está vazia. Uma árvore é vazia se não possuir raíz.
 * Retorno booleano (se a árvore for inexistente retorna `NULL_ERROR`, ao invés disso).
 */
int8_t is_empty_tree(Tree *bt);

/* Acessa o nó com o maior identificador na árvore.
 * Note que o maior sempre será o último nó mais à direita na árvore.
 * Retorno: `NULL_ERROR`, `EMPTY_ERROR`, `OK`.
 */
int8_t get_tree_higher_node(Tree *, void **r_element);

/* Retorna a quantidade de folhas da árvore. - Uma folha é um nó que não possui filhos.
 * Se a árvore não existir retorna `NULL_ERROR`, ao invés disso.
 */
int32_t leaves_count(Tree *);

/* Acessa o nó com o menor identificador na árvore, restrito por um valor mínimo.
 * Note que o menor sempre será o último nó mais à esquerda na árvore - a aplicação da restrição
 * deslocará esse valor: o valor será maior ou igual a esse mínimo.
 * Retorno: `NULL_ERROR`, `EMPTY_ERROR`, `NOT_OK`, `OK`.
 */
int8_t get_tree_nearest_lower(Tree *, int min, void **r_);

/* Imprime uma representação da árvore. */
int8_t print_tree(Tree *avl_tree);
