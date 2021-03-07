#include "ponto.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
/* No arquivo que usaremos o TAD (nesse caso, o programa principal) incluímos o caminho do arquivo
de cabeçalho `.h` que contém informações sobre o tipo de dado. Dizemos que estamos 'importando uma
biblioteca'. */


/* Faz uso do TAD declarado em "ponto.h". */
int main()
{
	setlocale(LC_ALL, "Portuguese");

	int i;
	/* Coordenas. */
	float cx, cy;
	// Cache da entrada.

	/* Pontos. */
	Ponto *p1, *p2;

	printf("Insira as cordenadas de dois pontos abaixo:\n");
	printf("Ponto 1\nCoordenada x = ");
	scanf("%f", &cx);
	printf("Coordenada y = ");
	scanf("%f", &cy);
	p1 = cria(cx, cy);

	printf("Ponto 2\nCoordenada x = ");
	scanf("%f", &cx);
	printf("Coordenada y = ");
	scanf("%f", &cy);
	p2 = cria(cx, cy);

	printf("Distância entre Ponto 1 e Ponto 2 é igual a %f.\n", distancia(p1, p2));
	libera(p1);
	libera(p2);
	p1 = NULL;
	p2 = NULL;

	/* A função `libera()` não foi usada aqui, pois o programa será encerrado logo em seguida após
	o seu uso, logo não é necessário já que toda a memória do programa será desalocada no fim da
	execução. Porém, para programas maiores, é importante remover a memória que não estiver sendo
	usada. Outro caso, seria no uso de laços que fazem alocação sobre demanda. */
	return 0;
}
