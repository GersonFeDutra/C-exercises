#include <locale.h>

/* 6. Crie uma fun��o que tem como par�metros um vetor de cidades, o c�digo de uma cidade,
e o tamanho do vetor. A fun��o deve retornar um ponteiro que possui o endere�o da
cidade no vetor que tem o c�digo passado como par�metro. Caso n�o exista uma cidade
com o c�digo passado, imprima na tela: "CIDADE INEXISTENTE".
struct cidade* buscar_cidade(struct cidade cidades[], int codigo, int tam); */
#include "ex06.h"


/* Usa a fun��o `buscar_cidade()` definida em "ex06.h" */
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
	printf("Qual c�digo deseja buscar? ");
	scanf("%d", &code);
	
	struct cidade *cid = buscar_cidade(c, code, CITIES);
	
	print_cidade(cid);
	
	return 0;
}

