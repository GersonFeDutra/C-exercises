#include <locale.h>

/* 5. Crie um procedimento que tem como parâmetros um vetor de cidades e o tamanho do
vetor. Imprima as informações de todas as cidades registradas no vetor.
void listar_cidades(struct cidade cidades[], int tam); */
#include "ex05.h"


/* Usa a função `listar_cidades()` definida em "ex05.h" */
int main() {
	setlocale(LC_ALL, "Portuguese");
	
	int i;
	const int CITIES = 3;
	struct cidade c[CITIES];
	
	for (i = 0; i < CITIES; ++i) {
		c[i] = gera_cidade();
		printf("\n");
	}
	listar_cidades(c, CITIES);
	
	return 0;
}

