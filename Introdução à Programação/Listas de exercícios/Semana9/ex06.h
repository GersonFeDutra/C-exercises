#include <string.h>
#include "ex05.h"  // structs: cidade / fun��es: fahrenheit(), print_cidade(), gera_cidade()


/* 6. Crie uma fun��o que tem como par�metros um vetor de cidades, o c�digo de uma cidade,
e o tamanho do vetor. A fun��o deve retornar um ponteiro que possui o endere�o da
cidade no vetor que tem o c�digo passado como par�metro. Caso n�o exista uma cidade
com o c�digo passado, imprima na tela: "CIDADE INEXISTENTE".
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

