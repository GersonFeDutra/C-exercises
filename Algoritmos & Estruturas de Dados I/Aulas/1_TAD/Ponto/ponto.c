#include "ponto.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
/* No arquivo que  o TAD (nesse caso, o programa principal) incluímos o caminho do arquivo
de cabeçalho `.h` que contém informações sobre o tipo de dado. Dizemos que estamos 'importando uma
biblioteca'. */

struct ponto {
	float x;
	float y;
};
/* Essa é a definição da estrutura (qual fora encapsulada pelo `typedef` declarado no cabeçalho) que
usaremos de fato  */


Ponto *cria(float x, float y)
{
	/* Esse método é equivalente a um 'construtor' em programação orientada à objetos */
	Ponto *p = (Ponto *)malloc(sizeof(Ponto));
	/* `malloc` retorna o ponteiro da estrutura alocada na heap como um `*void`, logo, atribuímos
	esse endereço à `p` por meio da coerção via `(Ponto *)`.*/

	if (p == NULL) {
		/* Após fazermos a alocação é importante verificarmos se ela foi realizada corretamente. Se
		algum erro ocorrer durante a alocação, encerramos a execução pois não haverá memória
		disponível para continuarmos processando. */
		printf("Memória insuficiente");
		exit(1);
	}

	p->x = x;
	// Equivalente à `(*p).x = x;`. Note que `(*p).x = x;` != `*p.x = x;` == `*(p.x) = x;`.
	// O operador `->` é uma forma de acessar uma estrutura por meio de um ponteiro.
	p->y = y;

	return p;
	// p contém o endereço do dado tipado como `Ponto` que foi retornado da alocação.
}


void libera(Ponto *p)
{
	free(p);
	/* Por mais simples que sejam as funções que operam o dado tipado, mantemos ela dentro do TAD
	para manter a consistência. */
}


void acessa(Ponto *p, float *x, float *y)
{
	/* Múltiplas variáveis podem ser "retornadas" por meio de ponteiros. O valor é então passado
	para o local apontado pelo endereço do ponteiro. Nesse caso, os valores são obtido por meio do
	ponteiro do dado tipado, uma `struct ponto`. */
	*x = p->x;
	*y = p->y;
}


void atribui(Ponto *p, float x, float y)
{
	/* Semelhante ao método `acessa()` atribuímos valores externos por meio de ponteiros. Mas, nesse
	caso, "retornamos" os valores, obtidos pelos múltiplos parâmetros passados para a função, no
	dado tipado (a `struct ponto`), ao contrário da função anterior. */
	p->x = x;
	p->y = y;
}


float distancia(Ponto *p1, Ponto *p2)
{
	float dx = p2->x - p1->x;
	float dy = p2->y - p1->y;

	return sqrtf(dx * dx + dy * dy);
}
