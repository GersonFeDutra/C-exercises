#include <stdio.h>

struct cadastro {
	char nome[20];
	char endereco[30];
	int idade;
};


int main() {
	FILE *fp;
	fp = fopen("struct.txt", "rb");
	
	if (fp == NULL) {
		printf("Erro ao abrir o arquivo");
		return -1;
	}
	
	struct cadastro cad;
	fread(&cad, sizeof(struct cadastro), 1, fp);
	printf("Nome: %s; End: %s; Idade: %d\n", cad.nome, cad.endereco, cad.idade);
	fread(&cad, sizeof(struct cadastro), 1, fp);
	printf("Nome: %s; End: %s; Idade: %d\n", cad.nome, cad.endereco, cad.idade);

	return 0;
}
