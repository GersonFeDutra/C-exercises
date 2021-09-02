#include "avl_tree.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#define CHECK_TREE(BT)                                                                             \
	if (BT == NULL)                                                                                \
		return NULL_ERROR;                                                                         \
	if (*BT == NULL)                                                                               \
		return EMPTY_ERROR;

#define EXEC_ERROR(OPERATION)                                                                      \
	if (OPTERATION != OK) {                                                                        \
		printf("Erro de execução! Não foi possível inserir na pilha.\n");                          \
		exit(1);                                                                                   \
	}

struct node {
	struct node *left;
	void *element; // Ponteiro genérico para um dado elemento.
	int32_t key;
	struct node *right;
} typedef *Node;


/* Funções "privadas" */

/* Função auxiliar recursiva para eliminar nós da árvore.
 * Irá destruir uma subárvore, em que o nó passado é a raíz - eliminando também os seus dados.
 */
static void _free_subtree(Node node)
{
	if (node == NULL)
		return;

	_free_subtree(node->left);
	// Não precisamos setar o apontamento para `NULL`, pois o nó será eliminado logo em seguida.
	// node->left = NULL;
	_free_subtree(node->right);
	// node->right = NULL;
	free(node->element);
	free(node);
}


/* Função auxiliar recursiva para eliminar nós da árvore.
 * Irá destruir uma subárvore, em que o nó passado é a raíz - eliminando apenas as referências.
 */
// static void _remove_node(Node node)
// {
// 	if (node == NULL)
// 		return;
//
// 	_remove_node(node->left);
// 	_remove_node(node->right);
// 	free(node);
// }


/* Função auxiliar recursiva para imprimir os nós na ordem em que são acessados na árvore. */
static void _pre_order(Node node)
{
	if (node == NULL)
		return;

	printf("%d ", node->key);
	_pre_order(node->left);
	_pre_order(node->right);
}


/* Função auxiliar recursiva para imprimir a árvore, imprimindo os nós da esquerda primeiro. */
static void _in_order(Node node)
{
	if (node == NULL)
		return;

	_in_order(node->left);
	printf("%d ", node->key);
	_in_order(node->right);
}


/* Função auxiliar recursiva para imprimir a árvore:
imprime os nós de ambos os lados, antes de imprimir um nó pai. */
static void _post_order(Node node)
{
	if (node == NULL)
		return;

	_post_order(node->left);
	_post_order(node->right);
	printf("%d ", node->key);
}


/* Função auxiliar recursiva que verifica a altura/ profundidade de um nó. */
static uint32_t _node_depth(Node node)
{
	if (node == NULL)
		return 0;

	uint32_t left = _node_depth(node->left);
	uint32_t right = _node_depth(node->right);
	// Percorremos as subárvores dos filhos do nó passado e buscamos a maior altura dentre elas.
	// Note que a cada nível percorrido somamos 1 nó valor final.

	return (left > right ? left : right) + 1;
}


/* Retorna a quantidade de nós da subárvore, com o nó passado como raíz. */
static uint32_t _count_nodes(Node node)
{
	if (node == NULL)
		return 0;

	return _count_nodes(node->left) + _count_nodes(node->right) + 1;
}


/* Busca o nó, com o identificador indicado, na subárvore em que o nó passado é a raíz.
Caso não seja encontrado, a função retorna `NULL`. */
static Node _get_node(Node node, int32_t key)
{
	Node aux = node;

	while (aux != NULL)
		if (key < aux->key)
			aux = aux->left;
		else if (key > aux->key)
			aux = aux->right;
		else
			break;

	return aux;
}


/* Retorna a quantidade de folhas da subárvore, com o nó passado como raíz. */
static uint32_t _count_leaves(Node node)
{
	if (node == NULL)
		return 0;

	if (node->left == NULL && node->right == NULL)
		return 1;

	return _count_leaves(node->left) + _count_leaves(node->right);
}


/* Função auxiliar que elimina um nó 'in-place' - elimina apenas um único nó e corrigindo a
 * estrutura de árvore AVL para os nós restantes.
 * Retorna o elemento do nó eliminado;
 * Se o nó com a chave indicada não for encontrado, retorna `NULL`, ao invés disso.
 */
static void *_free_node(Tree *avl_tree, int32_t key)
{
	Node aux = *avl_tree; // O nó que será removido.
	Node parent = NULL;   // O pai do nó que será removido.
	void *element = NULL; // O elemento que será retornado.

	while (aux != NULL)
		// Procuramos o nó a ser removido.
		if (key < aux->key) {
			parent = aux;
			aux = aux->left;
		}
		else if (key > aux->key) {
			parent = aux;
			aux = aux->right;
		}
		// Com o nó encontrado, fazemos sua remoção.
		else {
			if (aux->left != NULL && aux->right != NULL) {
				// Dois filhos:
				/* Buscamos um nó numa das subárvores de um dos lados do nó que será removido para
				substituir pelo nó atual, e manter a árvore com as propriedades corretas.
				Nesse caso, estamos em busca do nó com o maior identificador à esquerda do nó que
				será removido, mas também poderíamos implementar essa substituição buscando o nó com
				o menor identificador à direita. */
				Node higher_parent = aux;
				Node higher = aux->left;

				// Procuramos o nó com o maior identificar e o seu pai.
				// Note que o maior nó sempre será o último nó mais a direita na subárvore.
				while (higher->right != NULL) {
					higher_parent = higher;
					higher = higher->right;
				}
				/* Caso o nó com maior identificador não seja filho do auxiliar (que seria um caso
				especial no qual apenas deslocariamos a subárvore um nível acima): */
				if (higher_parent != aux) {
					higher_parent->right = higher->left; // Movemos a subárvore restante.
					higher->left = aux->left; // Deslocamos o nó para cima da subárvore.
				}
				higher->right = aux->right; // Terminamos de deslocar o nó.

				/* Por fim, anexamos o nó deslocado ao pai do que foi removido (ou, ao topo da
				árvore). */
				if (parent == NULL)
					*avl_tree = higher;
				else if (parent->left == aux)
					parent->left = higher;
				else
					parent->right = higher;
			}
			else if (aux->left == NULL && aux->right == NULL) {
				// Nenhum filho: Removemos uma folha.

				if (parent == NULL)
					*avl_tree = NULL; // Se o nó a ser removido for a raíz, basta limpar a árvore.

				// Esquerda / Right
				else if (parent->left == aux)
					parent->left = NULL;
				else
					parent->right = NULL;
			}
			else {
				// Um filho:
				// Anexamos a subárvore ao nó pai, substituíndo o nó que foi removido.

				if (parent == NULL)
					// Se o nó a ser removido for a raíz, a atualizamos para a subárvore do nó.
					if (aux->left != NULL)
						*avl_tree = aux->left;
					else
						*avl_tree = aux->right;

				// Esquerda / Direita
				else if (parent->left == aux)
					if (aux->left != NULL)
						parent->left = aux->left;
					else
						parent->left = aux->right;
				else {
					if (aux->left != NULL)
						parent->right = aux->left;
					else
						parent->right = aux->right;
				}
			}

			element = aux->element;
			free(aux); // Com os apontamentos resolvidos, por fim, liberamos o nó.

			break;
		}

	return element;
}


static void _padding(char ch, int n)
{
	uint32_t i;

	for (i = 0; i < n; i++)
		putchar(ch);
}


static void _print_subtree(Node node, uint32_t level)
{
	int i;

	if (node == NULL) {
		_padding('\t', level);
		puts("~");
	}
	else {
		_print_subtree(node->right, level + 1);
		_padding('\t', level);
		printf("%d\n", node->key);
		_print_subtree(node->left, level + 1);
	}
}


/* Funções "públicas" */

Tree *new_tree()
{
	Tree *avl_tree;
	avl_tree = (Tree *)malloc(sizeof(Tree));

	if (avl_tree != NULL)
		*avl_tree = NULL;

	return avl_tree;
}


// void clear_tree(Tree *avl_tree)
// {
// 	if (avl_tree != NULL) {
// 		_remove_node(*avl_tree); // Passamos o nó da raiz para iniciar o processo.
// 		*avl_tree = NULL;        // Não podemos esquecer de definir o apontamento para nulo;
//
// 		// Opcional: elimina a árvore como um todo.
// 		// free(avl_tree);
// 	}
// }


void free_nodes(Tree *avl_tree)
{
	if (avl_tree != NULL) {
		_free_subtree(*avl_tree);
		*avl_tree = NULL;

		// Opcional: elimina a árvore como um todo.
		// free(avl_tree);
	}
}


int8_t travel_tree(Tree *avl_tree, int8_t type)
{
	if (avl_tree == NULL)
		return NULL_ERROR;

	// Note que, se a árvore for vazia, nada será impresso.
	switch (type) {
		case -1: _pre_order(*avl_tree); break;
		case 0: _in_order(*avl_tree); break;
		case 1: _post_order(*avl_tree); break;
		default: return NOT_OK;
	}

	return OK;
}


int32_t tree_depth(Tree *avl_tree)
{
	if (avl_tree == NULL)
		return NULL_ERROR;

	// A altura da árvore é a altura da raiz;
	return _node_depth(*avl_tree);
}


int32_t node_depth(Tree *avl_tree, int32_t key)
{
	CHECK_TREE(avl_tree)

	// Equivalente a função `_altura_nó`, porém, com busca.
	return _node_depth(_get_node(*avl_tree, key));
}


int32_t node_count(Tree *avl_tree)
{
	if (avl_tree == NULL)
		return NULL_ERROR;

	// Note que se o nó passado for `NULL`, retornará 0.
	return _count_nodes(*avl_tree);
}


/* Funções próprias da Árvore Binária de Busca. */

int8_t insert_node(Tree *avl_tree, void *element, int32_t key)
{
	if (avl_tree == NULL)
		return NULL_ERROR;

	Node new = (Node)malloc(sizeof(struct node));

	if (new == NULL)
		return NOT_OK;

	new->element = element;
	new->left = NULL;
	new->right = NULL;
	new->key = key;
	// Um novo nó é sempre uma folha.

	if (*avl_tree == NULL)
		*avl_tree = new; // Inserimos a raíz da árvore.
	else {
		Node aux = *avl_tree;
		Node parent;
		// Começamos da raíz e vamos em busca do identificador (matrícula) mais próximo.

		// Procuramos a posição de inserção do novo nó.
		while (aux != NULL) {
			parent = aux;

			if (key < parent->key)
				aux = aux->left;
			else if (key > parent->key)
				aux = aux->right;
			else {
				/* Não podemos ter identificares iguais. Tentar inserir uma duplicata resultará em
				erro. */
				free(new);
				return INPUT_ERROR;
			}
		}

		// Novo nó é conectado ao pai dele na árvore.
		if (key < parent->key)
			parent->left = new;
		else
			parent->right = new;
	}

	return OK;
}


int8_t get_node(Tree *avl_tree, int32_t key, void **r_element)
{
	CHECK_TREE(avl_tree)
	Node aux = _get_node(*avl_tree, key);

	if (aux == NULL)
		return NOT_OK;

	*r_element = aux->element;
	return OK;
}


// int8_t remove_node(Tree *avl_tree, int32_t key, void **r_element)
// {
// 	CHECK_TREE(avl_tree)
// 	*r_element = _free_node(avl_tree, key);
//
// 	if (*r_element == NULL)
// 		return NOT_OK;
//
// 	return OK;
// }


int8_t free_node(Tree *avl_tree, int32_t key)
{
	CHECK_TREE(avl_tree)
	void *element = _free_node(avl_tree, key);

	if (element == NULL)
		return NOT_OK;

	free(element);
	return OK;
}


int8_t is_empty_tree(Tree *avl_tree)
{
	if (avl_tree == NULL)
		return NULL_ERROR;
	else
		return *avl_tree == NULL;
}


int8_t get_tree_higher_node(Tree *avl_tree, void **r_element)
{
	CHECK_TREE(avl_tree)
	Node higher = *avl_tree;

	while (higher->right != NULL)
		higher = higher->right;

	*r_element = higher->element;

	return OK;
}


int32_t leaves_count(Tree *avl_tree)
{
	if (avl_tree == NULL)
		return NULL_ERROR;

	// Note que se o nó passado for `NULL`, retornará 0.
	return _count_leaves(*avl_tree);
}


int8_t get_tree_nearest_lower(Tree *avl_tree, int32_t min, void **out)
{
	CHECK_TREE(avl_tree)
	Node aux = *avl_tree;
	Node nearest_lower = NULL;

	while (aux != NULL)

		if (aux->key > min) {
			nearest_lower = aux;
			aux = aux->left;
		}
		else if (aux->key < min) {
			aux = aux->right;
		}
		else {
			nearest_lower = aux; // Encontrou exatamente `min`.
			break;
		}

	if (nearest_lower == NULL)
		return NOT_OK; // Não encontrou um menor restrito por `min`.

	*out = nearest_lower->element;

	return OK;
}


int8_t print_tree(Tree *avl_tree)
{
	if (avl_tree == NULL)
		return NULL_ERROR;

	_print_subtree(*avl_tree, 0);

	return OK;
}
