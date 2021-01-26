#include <string.h>
#include "ex05.h"  // structs: cidade / funções: fahrenheit(), print_cidade(), gera_cidade()


/* 6. Crie uma função que tem como parâmetros um vetor de cidades, o código de uma cidade,
e o tamanho do vetor. A função deve retornar um ponteiro que possui o endereço da
cidade no vetor que tem o código passado como parâmetro. Caso não exista uma cidade
com o código passado, imprima na tela: "CIDADE INEXISTENTE".
struct cidade* buscar_cidade(struct cidade cidades[], int codigo, int tam); */
struct cidade* buscar_cidade(struct cidade cidades[], int codigo, int tam) {
	int i;
	struct cidade *pc;
	
	for (i = 0; i < tam; i++) {
		if (cidades[i].codigo == codigo) {
			*pc = cidades[i];
			break;
		}
	}
	if (i == tam) {
		printf("CIDADE INEXISTENTE!\n");
		pc->codigo = 0;
		strcpy(pc->nome, "-");
		pc->temperaturaC = pc->temperaturaF = 0.0;
	}
	
	return pc;
}

