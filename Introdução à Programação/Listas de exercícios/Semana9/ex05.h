#include "ex03.h"  // structs: cidade / funções: fahrenheit(), print_cidade(), gera_cidade()


/* 5. Crie um procedimento que tem como parâmetros um vetor de cidades e o tamanho do
vetor. Imprima as informações de todas as cidades registradas no vetor.
void listar_cidades(struct cidade cidades[], int tam); */
void listar_cidades(struct cidade cidades[], int tam) {
	void print_cidade(struct cidade *c);
	int i;
	
	for (i = 0; i < tam; ++i) {
		print_cidade(&cidades[i]);
	}
}

