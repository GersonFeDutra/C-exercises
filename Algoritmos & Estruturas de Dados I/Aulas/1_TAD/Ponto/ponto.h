/* Ponto (x, y). */
typedef struct ponto Ponto;
// Tipo exportado.
/* O `typedef` é uma forma de facilitar a escrita do tipo, ele também serve para 'encapsular' a
estrutura que estará localizada no `.c`, já que arquivos externos não poderão acessá-la diretamente. */

/* Funções exportadas (protótipos) */

// Aloca e retorna um ponto de coordenas (x, y).
Ponto *cria(float x, float y);
/* Note que usamos ponteiro para nos referenciarmos ao TAD. Isso é necessário pois, como estamos
abstrairmos o tipo de dado, não faria sentido acessá-lo diretamente. */

// Libera a memória de um ponto previamente criado.
void libera(Ponto *p);

// Devolve os valores das coordenas de um ponto.
void acessa(Ponto *p, float *x, float *y);

// Atribui novos valores às coordenas de um ponto.
void atribui(Ponto *p, float x, float y);

// Retorna à distância euclidiana entre dois pontos.
float distancia(Ponto *p1, Ponto *p2);

/* No Header é necessário descrevermos cada uma das funções para indicar ao usuário do TAD suas
funcionalidades. A ideia do TAD é que "sua implementação foi esquecida", logo usamos o header para
documentar a "interface" daquele tipo de dado. */
