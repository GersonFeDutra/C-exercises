#include "binary_tree.h"
#include "queue.h"
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
	struct student data;
	struct node *right;
} typedef Node;


/* Funções "privadas" */

/* Função auxiliar recursiva para eliminar nós da árvore.
Irá destruir uma subárvore, em que o nó passado é a raíz. */
static void _free_node(Node *node)
{
	if (node == NULL)
		return;

	_free_node(node->left);
	// Não precisamos setar o apontamento para `NULL`, pois o nó será eliminado logo em seguida.
	// node->left = NULL;
	_free_node(node->right);
	// node->right = NULL;
	free(node);
}


/* Função auxiliar recursiva para imprimir os nós na ordem em que são acessados na árvore. */
static void _pre_order(Node *node)
{
	if (node == NULL)
		return;

	printf("%d ", node->data.id);
	_pre_order(node->left);
	_pre_order(node->right);
}


/* Função auxiliar recursiva para imprimir a árvore, imprimindo os nós da esquerda primeiro. */
static void _in_order(Node *node)
{
	if (node == NULL)
		return;

	_in_order(node->left);
	printf("%d ", node->data.id);
	_in_order(node->right);
}


/* Função auxiliar recursiva para imprimir a árvore:
imprime os nós de ambos os lados, antes de imprimir um nó pai. */
static void _post_order(Node *node)
{
	if (node == NULL)
		return;

	_post_order(node->left);
	_post_order(node->right);
	printf("%d ", node->data.id);
}


/* Função auxiliar recursiva que verifica a altura/ profundidade de um nó. */
static int _node_depth(Node *node)
{
	if (node == NULL)
		return 0;

	int left = _node_depth(node->left);
	int right = _node_depth(node->right);
	// Percorremos as subárvores dos filhos do nó passado e buscamos a maior altura dentre elas.
	// Note que a cada nível percorrido somamos 1 nó valor final.

	return (left > right ? left : right) + 1;
}


/* Retorna a quantidade de nós da subárvore, com o nó passado como raíz. */
static int _count_nodes(Node *node)
{
	if (node == NULL)
		return 0;

	return _count_nodes(node->left) + _count_nodes(node->right) + 1;
}


/* Busca o nó, com o identificador indicado, na subárvore em que o nó passado é a raíz.
Caso não seja encontrado, a função retorna `NULL`. */
static Node *_get_node(Node *node, int id)
{
	Node *aux = node;

	while (aux != NULL)
		if (id < aux->data.id)
			aux = aux->left;
		else if (id > aux->data.id)
			aux = aux->right;
		else
			break;

	return aux;
}


/* Retorna a quantidade de folhas da subárvore, com o nó passado como raíz. */
static int _count_leaves(Node *node)
{
	if (node == NULL)
		return 0;

	if (node->left == NULL && node->right == NULL)
		return 1;

	return _count_leaves(node->left) + _count_leaves(node->right);
}


/* Funções "públicas" */

Tree *new_tree()
{
	Tree *bt;
	bt = (Tree *)malloc(sizeof(Tree));

	if (bt != NULL)
		*bt = NULL;

	return bt;
}


void clear_tree(Tree *bt)
{
	if (bt != NULL) {
		_free_node(*bt); // Passamos o nó da raiz para iniciar o processo.
		*bt = NULL;      // Não podemos esquecer de definir o apontamento para nulo;

		// Opcional: elimina a árvore como um todo.
		// free(bt);
	}
}


int travel_tree(Tree *bt, int type)
{
	if (bt == NULL)
		return NULL_ERROR;

	// Note que, se a árvore for vazia, nada será impresso.
	switch (type) {
		case -1: _pre_order(*bt); break;
		case 0: _in_order(*bt); break;
		case 1: _post_order(*bt); break;
		default: return NOT_OK;
	}

	return OK;
}


// int print_tree(Tree *bt){}


int tree_depth(Tree *bt)
{
	if (bt == NULL)
		return NULL_ERROR;

	// A altura da árvore é a altura da raiz;
	return _node_depth(*bt);
}


int node_depth(Tree *bt, int id)
{
	CHECK_TREE(bt)

	// Equivalente a função `_altura_nó`, porém, com busca.
	return _node_depth(_get_node(*bt, id));
}


int node_count(Tree *bt)
{
	if (bt == NULL)
		return NULL_ERROR;

	// Note que se o nó passado for `NULL`, retornará 0.
	return _count_nodes(*bt);
}


/* Funções próprias da Árvore Binária de Busca. */

int insert_node(Tree *bt, struct student data)
{
	if (bt == NULL)
		return NULL_ERROR;

	Node *new = (Node *)malloc(sizeof(Node));

	if (new == NULL)
		return NOT_OK;

	new->data = data;
	new->left = NULL;
	new->right = NULL;
	// Um novo nó é sempre uma folha.

	if (*bt == NULL)
		*bt = new; // Inserimos a raíz da árvore.
	else {
		Node *aux = *bt, *parent;
		// Começamos da raíz e vamos em busca do identificador (matrícula) mais próximo.

		// Procuramos a posição de inserção do novo nó.
		while (aux != NULL) {
			parent = aux;

			if (data.id < parent->data.id)
				aux = aux->left;
			else if (data.id > parent->data.id)
				aux = aux->right;
			else {
				/* Não podemos ter identificares iguais. Tentar inserir uma duplicata resultará em
				erro. */
				free(new);
				return INPUT_ERROR;
			}
		}

		// Novo nó é conectado ao pai dele na árvore.
		if (data.id < parent->data.id)
			parent->left = new;
		else
			parent->right = new;
	}

	return OK;
}


int get_node(Tree *bt, int id, struct student *out)
{
	CHECK_TREE(bt)

	// Ambos os códigos são equivalentes.
	// Node *aux = _get_node(*bt, id);
	// if (aux != NULL) {
	// 	*out = aux->data;
	// 	return OK;
	// } // Deixei esse comentado apenas por quê tem um `if` a mais. :P

	Node *aux = *bt;
	while (aux != NULL)
		if (id < aux->data.id)
			aux = aux->left;
		else if (id > aux->data.id)
			aux = aux->right;
		else {
			*out = aux->data;
			return OK;
		}

	return NOT_OK;
}


int remove_node(Tree *bt, int id)
{
	CHECK_TREE(bt)
	Node *aux = *bt;     // O nó que será removido.
	Node *parent = NULL; // O pai do nó que será removido.

	while (aux != NULL)
		// Procuramos o nó a ser removido.
		if (id < aux->data.id) {
			parent = aux;
			aux = aux->left;
		}
		else if (id > aux->data.id) {
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
				Node *higher_parent = aux, *higher = aux->left;

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
					*bt = higher;
				else if (parent->left == aux)
					parent->left = higher;
				else
					parent->right = higher;
			}
			else if (aux->left == NULL && aux->right == NULL) {
				// Nenhum filho: Removemos uma folha.

				if (parent == NULL)
					*bt = NULL; // Se o nó a ser removido for a raíz, basta limpar a árvore.

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
						*bt = aux->left;
					else
						*bt = aux->right;

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

			free(aux); // Com os apontamentos resolvidos, por fim, liberamos o nó.
			return OK;
		}

	return NOT_OK; // Nó não foi encontrado.
}


int is_empty_tree(Tree *bt)
{
	if (bt == NULL)
		return NULL_ERROR;
	else
		return *bt == NULL;
}


int get_tree_higher_node(Tree *bt, struct student *out)
{
	CHECK_TREE(bt)
	Node *higher = *bt;

	while (higher->right != NULL)
		higher = higher->right;

	*out = higher->data;

	return OK;
}


int leaves_count(Tree *bt)
{
	if (bt == NULL)
		return NULL_ERROR;

	// Note que se o nó passado for `NULL`, retornará 0.
	return _count_leaves(*bt);
}


int get_tree_nearest_lower(Tree *bt, int min, struct student *out)
{
	CHECK_TREE(bt)
	Node *aux = *bt, *nearest_lower = NULL;

	while (aux != NULL)

		if (aux->data.id > min) {
			nearest_lower = aux;
			aux = aux->left;
		}
		else if (aux->data.id < min) {
			aux = aux->right;
		}
		else {
			nearest_lower = aux; // Encontrou exatamente `min`.
			break;
		}

	if (nearest_lower == NULL)
		return NOT_OK; // Não encontrou um menor restrito por `min`.

	*out = nearest_lower->data;

	return OK;
}


/* Imprime a árvore de acordo com o nível de profundidade. */
void print_tree_by_level(Tree *bt)
{
	if (bt == NULL)
		return;

	Queue *queue = new_queue();

	if (queue == NULL) {
		printf("Memory error!");
		return;
	}

	Node *current;
	add_to_queue(queue, *bt); // Assert
	printf("BT");

	while (queue_get(queue, (void *)&current) == OK) {
		printf(" %d", current->data.id);
		remove_from_queue(queue); // Assert

		if (current->left != NULL)
			add_to_queue(queue, current->left);

		if (current->right != NULL)
			add_to_queue(queue, current->right);
	}

	free_queue(&queue);
}
