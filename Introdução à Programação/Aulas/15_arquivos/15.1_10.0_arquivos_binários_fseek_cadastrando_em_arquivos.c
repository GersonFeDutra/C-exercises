#include <stdio.h>

struct produto {
	char nome[20];
	int quantidade;
	float preco;
};


int main() {
	FILE *fp;
	fp = fopen("mercadorias.txt", "wb");
	
	if (fp == NULL) {
		printf("Erro ao abrir o arquivo");
		return -1;
	}
	
	struct produto mercadorias[4] = {
		{"Chocolate", 100, 2.5},
		{"Abacate", 20, 4.9},
		{"Alface", 40, 4.9},
		{"Pera", 30, 7.9}
	};
	fwrite(mercadorias, sizeof(struct produto), 4, fp);
	fclose(fp);

	return 0;
}
