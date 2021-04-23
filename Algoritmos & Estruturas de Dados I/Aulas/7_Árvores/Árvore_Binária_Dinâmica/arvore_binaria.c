#include "arvore_binaria.h"
#include <stdio.h>
#include <stdlib.h>

#define VERIFICAR_ARVORE(AB)                                                                       \
	if (AB == NULL)                                                                                \
		return NULL_ERROR;                                                                         \
	if (*AB == NULL)                                                                               \
		return EMPTY_ERROR;

struct no {
	struct no *esquerda;
	struct aluno dados;
	struct no *direita;
} typedef No;


/* Funções "privadas" */

/* Função auxiliar recursiva para eliminar nós da árvore.
Irá destruir uma subárvore, em que o nó passado é a raíz. */
static void _liberar_no(No *no)
{
	if (no == NULL)
		return;

	_liberar_no(no->esquerda);
	// Não precisamos setar o apontamento para `NULL`, pois o nó será eliminado logo em seguida.
	// no->esquerda = NULL;
	_liberar_no(no->direita);
	// no->direita = NULL;
	free(no);
}


/* Função auxiliar recursiva para imprimir os nós na ordem em que são acessados na árvore. */
static void _pre_ordem(No *no)
{
	if (no == NULL)
		return;

	printf("%d ", no->dados.matricula);
	_pre_ordem(no->esquerda);
	_pre_ordem(no->direita);
}


/* Função auxiliar recursiva para imprimir a árvore, imprimindo os nós da esquerda primeiro. */
static void _em_ordem(No *no)
{
	if (no == NULL)
		return;

	_em_ordem(no->esquerda);
	printf("%d ", no->dados.matricula);
	_em_ordem(no->direita);
}


/* Função auxiliar recursiva para imprimir a árvore:
imprime os nós de ambos os lados, antes de imprimir um nó pai. */
static void _pos_ordem(No *no)
{
	if (no == NULL)
		return;

	_pos_ordem(no->esquerda);
	_pos_ordem(no->direita);
	printf("%d ", no->dados.matricula);
}


/* Função auxiliar recursiva que verifica a altura/ profundidade de um nó. */
static int _altura_no(No *no)
{
	if (no == NULL)
		return 0;

	int esquerda = _altura_no(no->esquerda);
	int direita = _altura_no(no->direita);
	// Percorremos as subárvores dos filhos do nó passado e buscamos a maior altura dentre elas.
	// Note que a cada nível percorrido somamos 1 no valor final.

	return (esquerda > direita ? esquerda : direita) + 1;
}


/* Retorna a quantidade de nós da subárvore, com o nó passado como raíz. */
static int _contar_nos(No *no)
{
	if (no == NULL)
		return 0;

	return _contar_nos(no->esquerda) + _contar_nos(no->direita) + 1;
}


/* Busca o nó, com o identificador indicado, na subárvore em que o nó passado é a raíz.
Caso não seja encontrado, a função retorna `NULL`. */
static No *_buscar_no(No *no, int matricula)
{
	No *aux = no;

	while (aux != NULL)
		if (matricula < aux->dados.matricula)
			aux = aux->esquerda;
		else if (matricula > aux->dados.matricula)
			aux = aux->direita;
		else
			break;

	return aux;
}

/* Funções "públicas" */

Arvore *criar_arvore()
{
	Arvore *ab;
	ab = (Arvore *)malloc(sizeof(Arvore));

	if (ab != NULL)
		*ab = NULL;

	return ab;
}


void limpar_arvore(Arvore *ab)
{
	if (ab != NULL) {
		_liberar_no(*ab); // Passamos o nó da raiz para iniciar o processo.
		*ab = NULL; // Não podemos esquecer de definir o apontamento para nulo;

		// Opcional: elimina a árvore como um todo.
		// free(ab);
	}
}


int percorrer(Arvore *ab, int tipo)
{
	if (ab == NULL)
		return NULL_ERROR;

	// Note que, se a árvore for vazia, nada será impresso.
	switch (tipo) {
		case -1: _pre_ordem(*ab); break;
		case 0: _em_ordem(*ab); break;
		case 1: _pos_ordem(*ab); break;
		default: return NOT_OK;
	}

	return OK;
}


// int print_arvore(Arvore *ab){}


int altura(Arvore *ab)
{
	if (ab == NULL)
		return NULL_ERROR;

	// A altura da árvore é a altura da raiz;
	return _altura_no(*ab);
}


int altura_no(Arvore *ab, int matricula)
{
	VERIFICAR_ARVORE(ab)

	// Equivalente a função `_altura_nó`, porém, com busca.
	return _altura_no(_buscar_no(*ab, matricula));
}


int quantidade_nos(Arvore *ab)
{
	if (ab == NULL)
		return NULL_ERROR;

	// Note que se o nó passado for `NULL`, retornará 0.
	return _contar_nos(*ab);
}


/* Funções próprias da Árvore Binária de Busca. */

int inserir_no(Arvore *ab, struct aluno dados)
{
	if (ab == NULL)
		return NULL_ERROR;

	No *novo = (No *)malloc(sizeof(No));

	if (novo == NULL)
		return NOT_OK;

	novo->dados = dados;
	novo->esquerda = NULL;
	novo->direita = NULL;
	// Um novo nó é sempre uma folha.

	if (*ab == NULL)
		*ab = novo; // Inserimos a raíz da árvore.
	else {
		No *aux = *ab, *pai;
		// Começamos da raíz e vamos em busca do identificador (matrícula) mais próximo.

		// Procuramos a posição de inserção do novo nó.
		while (aux != NULL) {
			pai = aux;

			if (dados.matricula < pai->dados.matricula)
				aux = aux->esquerda;
			else if (dados.matricula > pai->dados.matricula)
				aux = aux->direita;
			else {
				/* Não podemos ter identificares iguais. Tentar inserir uma duplicata resultará em
				erro. */
				free(novo);
				return INPUT_ERROR;
			}
		}

		// Novo nó é conectado ao pai dele na árvore.
		if (dados.matricula < pai->dados.matricula)
			pai->esquerda = novo;
		else
			pai->direita = novo;
	}

	return OK;
}


int acessar_no(Arvore *ab, int matricula, struct aluno *saida)
{
	VERIFICAR_ARVORE(ab)

	// Ambos os códigos são equivalentes.
	// No *aux = _buscar_no(*ab, matricula);
	// if (aux != NULL) {
	// 	*saida = aux->dados;
	// 	return OK;
	// } // Deixei esse comentado apenas por quê tem um `if` a mais. :P

	No *aux = *ab;
	while (aux != NULL)
		if (matricula < aux->dados.matricula)
			aux = aux->esquerda;
		else if (matricula > aux->dados.matricula)
			aux = aux->direita;
		else {
			*saida = aux->dados;
			return OK;
		}

	return NOT_OK;
}


int remover_no(Arvore *ab, int matricula)
{
	VERIFICAR_ARVORE(ab)
	No *aux = *ab;  // O nó que será removido.
	No *pai = NULL; // O pai do nó que será removido.

	while (aux != NULL)
		// Procuramos o nó a ser removido.
		if (matricula < aux->dados.matricula) {
			pai = aux;
			aux = aux->esquerda;
		}
		else if (matricula > aux->dados.matricula) {
			pai = aux;
			aux = aux->direita;
		}
		// Com o nó encontrado, fazemos sua remoção.
		else {
			if (aux->esquerda != NULL && aux->direita != NULL) {
				// Dois filhos:
				/* Buscamos um nó numa das subárvores de um dos lados do nó que será removido para
				substituir pelo nó atual, e manter a árvore com as propriedades corretas.
				Nesse caso, estamos em busca do nó com o maior identificador à esquerda do nó que
				será removido, mas também poderíamos implementar essa substituição buscando o nó com
				o menor identificador à direita. */
				No *pai_maior = aux, *maior = aux->esquerda;

				// Procuramos o nó com o maior identificar e o seu pai.
				// Note que o maior nó sempre será o último nó mais a direita na subárvore.
				while (maior->direita != NULL) {
					pai_maior = maior;
					maior = maior->direita;
				}
				/* Caso o nó com maior identificador não seja filho do auxiliar (que seria um caso
				especial no qual apenas deslocariamos a subárvore um nível acima): */
				if (pai_maior != aux) {
					pai_maior->direita = maior->esquerda; // Movemos a subárvore restante.
					maior->esquerda = aux->esquerda; // Deslocamos o nó para cima da subárvore.
				}
				maior->direita = aux->direita; // Terminamos de deslocar o nó.

				/* Por fim, anexamos o nó deslocado ao pai do que foi removido (ou, ao topo da
				árvore). */
				if (pai == NULL)
					*ab = maior;
				else if (pai->esquerda == aux)
					pai->esquerda = maior;
				else
					pai->direita = maior;
			}
			else if (aux->esquerda == NULL && aux->direita == NULL) {
				// Nenhum filho: Removemos uma folha.

				if (pai == NULL)
					*ab = NULL; // Se o nó a ser removido for a raíz, basta limpar a árvore.

				// Esquerda / Direita
				else if (pai->esquerda == aux)
					pai->esquerda = NULL;
				else
					pai->direita = NULL;
			}
			else {
				// Um filho:
				// Anexamos a subárvore ao nó pai, substituíndo o nó que foi removido.

				if (pai == NULL)
					// Se o nó a ser removido for a raíz, a atualizamos para a subárvore do nó.
					if (aux->esquerda != NULL)
						*ab = aux->esquerda;
					else
						*ab = aux->direita;

				// Esquerda / Direita
				else if (pai->esquerda == aux)
					if (aux->esquerda != NULL)
						pai->esquerda = aux->esquerda;
					else
						pai->esquerda = aux->direita;
				else {
					if (aux->esquerda != NULL)
						pai->direita = aux->esquerda;
					else
						pai->direita = aux->direita;
				}
			}

			free(aux); // Com os apontamentos resolvidos, por fim, liberamos o nó.
			return OK;
		}

	return NOT_OK; // Nó não foi encontrado.
}


int vazia(Arvore *ab)
{
	if (ab == NULL)
		return NULL_ERROR;
	else
		return *ab == NULL;
}
