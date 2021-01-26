#include <stdio.h>

struct produto {
	char nome[20];
	int quantidade;
	float preco;
};



int main() {
	FILE *fp;
	fp = fopen("mercadorias.txt", "rb");
	
	if (fp == NULL) {
		printf("Erro ao abrir o arquivo");
		return -1;
	}
	
	struct produto p;
	fseek(fp, 3 * sizeof(struct produto), SEEK_SET);
	fread(&p, sizeof(struct produto), 4, fp);
	printf("Nome do produto: %s\n", p.nome);
	printf("Quantidade: %d\n", p.quantidade);
	printf("Preco: %5.2f\n", p.preco);
	fclose(fp);

	return 0;
}
