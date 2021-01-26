#include <locale.h>

/* 6. Crie uma função que tem como parâmetros um vetor de cidades, o código de uma cidade,
e o tamanho do vetor. A função deve retornar um ponteiro que possui o endereço da
cidade no vetor que tem o código passado como parâmetro. Caso não exista uma cidade
com o código passado, imprima na tela: "CIDADE INEXISTENTE".
struct cidade* buscar_cidade(struct cidade cidades[], int codigo, int tam); */
#include "ex06.h"


/* Usa a função `buscar_cidade()` definida em "ex06.h" */
int main() {
	struct cidade* buscar_cidade(struct cidade cidades[], int codigo, int tam);
	void print_cidade(struct cidade *c);
	setlocale(LC_ALL, "Portuguese");
	
	int i;
	const int CITIES = 3;
	struct cidade c[CITIES];
	
	for (i = 0; i < CITIES; ++i) {
		c[i] = gera_cidade();
		printf("\n");
	}
	
	int code;
	printf("Qual código deseja buscar? ");
	scanf("%d", &code);
	
	struct cidade *cid = buscar_cidade(c, code, CITIES);
	
	print_cidade(cid);
	
	return 0;
}

