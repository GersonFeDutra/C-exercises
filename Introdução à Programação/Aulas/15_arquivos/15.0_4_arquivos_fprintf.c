#include <stdio.h>
#include <string.h>


int main() {
	char nome[] = "Nelson";
	int i = 32;
	float h = 1.68;
	FILE *fp;
	fp = fopen("arq_fprintf.txt", "w");
	
	if (fp == NULL) {
		printf("Erro ao abrir o arquivo");
		return -1;
	}
	
	fprintf(fp, "Nome: %s\nIdade: %d\nAltura: %f", nome, i, h);
	fclose(fp);

	return 0;
}
