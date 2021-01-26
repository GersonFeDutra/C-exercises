#include <locale.h>
#include "ex07.h"  // structs: cidade / funções: fahrenheit(), print_cidade(), gera_cidade(), listar_cidades(), buscar_cidade(), altera_temperatura()

#define CITIES 3

/* 8. Na função principal (após ter criado as 3 cidades), exiba as opções:
[1] - Listar cidades,
[2] - Alterar temperatura de cidade,
[0] - Sair.
Se o usuário digitar 1, exiba a lista de cidades para ele (com as informações de cada uma).
Após isso, exiba novamente a mensagem inicial com as 3 opções. Caso ele digite 2, pergunte
para ele o código da cidade e a quantidade de graus em celsius que ele deseja alterar.
Atualize a temperatura da cidade (usando as funções de buscar cidade e alterar temperatura)
e, após isso, mostre novamente as opções iniciais para o usuário. Caso o usuário digite 0,
finalize o programa. */


int main() {
	void listar_cidades(struct cidade cidades[], int tam);
	int buscar();
	void alterar(struct cidade *c);
	struct cidade* buscar_cidade(struct cidade cidades[], int codigo, int tam);
	setlocale(LC_ALL, "Portuguese");
	
	/* Preenche as cidades */
	struct cidade cidades[CITIES];
	int i;
	
	for (i = 0; i < CITIES; ++i) {
		cidades[i] = gera_cidade();
		printf("\n");
	}
	
	while(1) {
		system("pause");
		system("cls");
		
		switch (menu()) {
			case 0: return 0;
			case 1: listar_cidades(cidades, CITIES); break;
			case 2: alterar(buscar_cidade(cidades, buscar(), CITIES));
		}
	}
}


int menu() {
	int option;
	
	printf("[1] - Listar cidades\n");
	printf("[2] - Alterar temperatura de cidade\n");
	printf("[0] - Sair\n");
	printf(">>> ");
	scanf("%d", &option);
	
	return option;
}


int buscar() {
	int code;
	
	printf("Qual código deseja buscar? ");
	scanf("%d", &code);
	
	return code;
}

void alterar(struct cidade *c) {
	void altera_temperatura(struct cidade *cid, float numero);
	
	if (c->nome == "-") {
		printf("\nErro de busca, por favor tente novamente!\n");
		return;
	}
	
	float graus;
	print_cidade(c);
	
	printf("\nDeseja alterar a temperatura da cidade em quantos graus? °C ");
	scanf("%f", &graus);
	
	altera_temperatura(c, graus);
	
	printf("\nOperação realizada com sucesso!\n");
	print_cidade(c);
}

