#include <stdio.h>


int main() {
	char nome[20];
	char texto[20];
	int i;
	float h;
	FILE *fp;
	fp = fopen("arq_fprintf.txt", "r");
	
	if (fp == NULL) {
		printf("Erro ao abrir o arquivo");
		return -1;
	}
	
	fscanf(fp, "%s %s", texto, nome);
	printf("%s %s\n", texto, nome);
	
	fscanf(fp, "%s %d", texto, &i);
	printf("%s %d\n", texto, i);
	
	fscanf(fp, "%s %f", texto, &h);
	printf("%s %f\n", texto, h);
	fclose(fp);

	return 0;
}
