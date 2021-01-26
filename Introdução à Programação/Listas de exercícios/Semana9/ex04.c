#include <locale.h>
#include "ex03.h"  // structs: cidade / fun��es: fahrenheit(), print_cidade(), gera_cidade()

#define CITIES 3


/* 4. Na fun��o principal (main), crie um vetor do tipo estrutura cidade com 3 elementos.
Chame a fun��o que gera cidades 3 vezes e atribua cada cidade retornada para uma
regi�o do vetor. */
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

