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

#define MAX(A, B) (A > B) ? A : B

struct node {
	struct node *left;
	void *element; // Ponteiro genérico para um dado elemento.
	int32_t key;
	struct node *right;
	// Ter um registro da altura das subárvores de uma árvore AVL diminui a complexidade de suas
	// operações.
	int32_t height;
} typedef *Node;


/* Funções "privadas" */

/* Funções auxiliares genéricas de uma BST. */

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


// WATCH
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


/* Funções auxiliares específicas de uma árvore AVL. */

/* Retorna a altura de um dado nó. */
static int32_t _get_node_height(Node node)
{
	if (node == NULL)
		return 0;

	return node->height;
}


/* Retorna o fator de balanço de um nó, de acordo com a altura de seus filhos.
 * Útil para determinar se uma árvore está balanceada ou não.
 */
static int32_t _get_node_balance(Node node)
{
	if (node == NULL)
		return 0;

	return _get_node_height(node->left) - _get_node_height(node->right);
}


/* Dada uma subárvore não-vazia, retorna o nó com a chave de menor valor. */
static Node _get_min_node(Node node)
{
	Node current = node;

	while (current->left != NULL)
		current = current->left;

	return current;
}


#define GET_NEW_HEIGHT(ROOT) MAX(_get_node_height(ROOT->left), _get_node_height(ROOT->right)) + 1


/* Função auxiliar que rotaciona uma subárvore de raíz `y` na direita. */
static Node _right_rotate(Node y)
{
	Node x = y->left;
	Node T2 = x->right;

	// Realiza a rotação.
	x->right = y;
	y->left = T2;

	// Atualiza as alturas
	y->height = GET_NEW_HEIGHT(y);
	x->height = GET_NEW_HEIGHT(x);

	return x; // `x` será a nova raíz da subárvore.
}


/* Função auxiliar que rotaciona uma subárvore de raíz `x` na esquerda. */
static Node _left_rotate(Node x)
{
	Node y = x->right;
	Node T2 = y->left;

	// Realiza a rotação
	y->left = x;
	x->right = T2;

	// Atualiza as alturas
	x->height = GET_NEW_HEIGHT(x);
	y->height = GET_NEW_HEIGHT(y);

	return y; // `y` será a nova raíz da subárvore.
}


// TODO -> Implementar o algoritmo de forma interativa usando o TAD Stack.
/* Função auxiliar recursiva que realiza a inserção de um nó na subárvore.
 * Retorna a raíz atualizada dessa subárvore.
 */
static Node _insert(Node node, void *element, int32_t key)
{
	/* Realiza a inserção normal de uma BST. */

	if (node == NULL) {
		// Novo nó que será inserido na árvore.
		Node new = (Node)malloc(sizeof(struct node));

		if (new == NULL)
			// Como estamos usando recursão não podemos tratar esse erro de memória nessa
			// profundidade. Etão apenas encerramos a execução.
			exit(1);

		new->element = element;
		new->left = NULL;
		new->right = NULL;
		new->key = key;
		new->height = 1;
		// Um novo nó é sempre uma folha.

		return new;
	}

	if (key < node->key)
		node->left = _insert(node->left, element, key);
	else if (key > node->key)
		node->right = _insert(node->right, element, key);
	else
		return node; // A inserção não é realizada pois a chave já existe.

	// Atualiza a altura do nó atual.
	node->height = GET_NEW_HEIGHT(node);

	/* Busca o fator de balanço do nó atual para verificar se se tornara desbalanceado. */
	int32_t balance = _get_node_balance(node);

	// Caso o nó se torne desbalanceado há quatro casos possíveis (1 para cada tipo de rotação):

	// Estamos na esquerda da da árvore.
	if (balance > 1)
		// Rotação Direita
		if (key < node->left->key) {
			return _right_rotate(node);
		}
		// Rotação Dupla Direita
		else if (key > node->left->key) {
			node->left = _left_rotate(node->left);
			return _right_rotate(node);
		}

	// Estamos na direita da da árvore.
	if (balance < -1)
		// Rotação Esquerda
		if (key > node->right->key) {
			return _left_rotate(node);
		}
		// Rotação Dupla Esquerda
		else if (key < node->right->key) {
			node->right = _right_rotate(node->right);
			return _left_rotate(node);
		}

	return node; // Retorna o nó sem alterações.
}


// Como usamos uma função recursiva para remover o nó, teríamos 3 soluções para tratar os dados
// removidos:
// 1 - Mudar o retorno da função para uma struct contendo o nó atual e os dados que foram removidas;
// pro: fácil implementação; con: requer que uma struct específica seja declarada para esse caso
// específico;
// 2 - Alterar a função para um algoritmo interativo (opção preferida); // TODO
// pro: não necessita declarar um tipo novo, e ocupa menos espaço na Stack; con: mais difícil de
// implentar;
// 3 - Usar uma global estática (no escopo do TAD);
// pro: mais fácil de implementar, não requer declaração de um tipo novo; con: variável de escopo
// aberto. <- Essa é opção que decidi implementar no momento.
static void *_removed_element = NULL;


static Node _free_node(Node root, uint8_t key)
{
	/* 1. Realiza uma remoção padrão da BST. */

	if (root == NULL)
		return root;

	if (key < root->key)
		root->left = _free_node(root->left, key);

	else if (key > root->key)
		root->right = _free_node(root->right, key);

	else {
		// Nó com apenas um filho ou sem filhos:
		if (root->left == NULL || root->right == NULL) {
			Node tmp = root->left != NULL ? root->left : root->right;

			// `root` é folha.
			if (tmp == NULL) {
				tmp = root;
				root = NULL;
			}
			else {
				*root = *tmp; // Copia o conteúdo da filha que não está vazia para a raíz.
			}

			// Delegamos os dados do nó removido para ser tratados externamente.
			_removed_element = tmp->element;
			free(tmp);
		}
		// Nó com dois filhos
		else {
			Node tmp = _get_min_node(root->right); // O menor sucessor da direita de `root`.
			// Copiamos o conteúdo desse sucessor para `root` e removemos este nó.
			root->key = tmp->key;
			root->element = tmp->element;
			root->right = _free_node(root->right, tmp->key);
		}
	}

	// Se a raíz tiver sido removida, nada mais precisa ser feito.
	if (root == NULL)
		return root;

	/* 2. Atualiza a altura do nó atual. E reestabelecemos o balanceamento, caso necessário. */
	root->height = GET_NEW_HEIGHT(root);

	int32_t balance = _get_node_balance(root);
	// Os casos possíveis são os mesmos da inserção:

	if (balance > 1) {
		int32_t left_balance = _get_node_balance(root->left);

		// Rotação Direita
		if (left_balance >= 0) {
			return _right_rotate(root);
		}
		// Rotação Dupla Direita
		else if (left_balance < 0) {
			root->left = _left_rotate(root->left);
			return _right_rotate(root);
		}
	}

	if (balance < -1) {
		int32_t right_balance = _get_node_balance(root->right);

		// Rotação Esquerda
		if (right_balance <= 0) {
			return _left_rotate(root);
		}
		// Rotação Dupla Esquerda
		else if (right_balance > 0) {
			root->right = _right_rotate(root->right);
			return _left_rotate(root);
		}
	}

	return root;
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

	*avl_tree = _insert(*avl_tree, element, key);

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
// 	*avl_tree = _free_node(avl_tree, key);
// 	*r_element = _removed_element;
// 
// 	if (*r_element == NULL)
// 		return NOT_OK;
// 
// 	return OK;
// }


int8_t free_node(Tree *avl_tree, int32_t key)
{
	CHECK_TREE(avl_tree)
	*avl_tree = _free_node(*avl_tree, key);

	// Assumindo que os dados do nó estavam vazios retornamos uma flag de erro.
	if (_removed_element == NULL)
		return NOT_OK;

	free(_removed_element);
	_removed_element = NULL;

	return OK;
}


int8_t is_empty_tree(Tree *avl_tree)
{
	if (avl_tree == NULL)
		return NULL_ERROR;
	else
		return *avl_tree == NULL;
}


int8_t get_tree_max_node(Tree *avl_tree, void **r_element)
{
	CHECK_TREE(avl_tree)
	Node higher = *avl_tree;

	while (higher->right != NULL)
		higher = higher->right;

	*r_element = higher->element;

	return OK;
}


int8_t get_tree_min_node(Tree *avl_tree, void **r_element)
{
	CHECK_TREE(avl_tree)
	*r_element = _get_min_node(*avl_tree)->element;

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
