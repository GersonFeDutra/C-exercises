#include <stdio.h>

struct cadastro {
	char nome[20];
	char endereco[30];
	int idade;
};


int main() {
	FILE *fp;
	fp = fopen("struct.txt", "wb");
	
	if (fp == NULL) {
		printf("Erro ao abrir o arquivo");
		return -1;
	}
	
	struct cadastro cad = {"Nelson", "Rua A", 32};
	struct cadastro cad2 = {"Arthur", "Rua B", 32};
	
	fwrite(&cad, sizeof(struct cadastro), 1, fp);
	fwrite(&cad2, sizeof(struct cadastro), 1, fp);
	fclose(fp);

	return 0;
}
