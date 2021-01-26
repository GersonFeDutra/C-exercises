#include <locale.h>
#include "ex03.h"  // structs: cidade / funções: fahrenheit(), print_cidade(), gera_cidade()

#define CITIES 3


/* 4. Na função principal (main), crie um vetor do tipo estrutura cidade com 3 elementos.
Chame a função que gera cidades 3 vezes e atribua cada cidade retornada para uma
região do vetor. */
int main() {
	void print_cidade(struct cidade *c);
	setlocale(LC_ALL, "Portuguese");
	
	int i;
	struct cidade c[CITIES];
	
	for (i = 0; i < CITIES; ++i) {
		c[i] = gera_cidade();
		printf("\n");
	}
	
	for (i = 0; i < CITIES; ++i) {
		print_cidade(&c[i]);
	}
	
	return 0;
}

