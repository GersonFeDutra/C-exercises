#include <stdio.h>


int main() {
	char str[20];
	FILE *fp;
	fp = fopen("arquivo.txt", "r");
	
	if (fp == NULL) {
		printf("Erro ao abrir o arquivo");
		return -1;
	}
	
	char* result = fgets(str, 12, fp);
	
	if (result == NULL)
		printf("Erro na leitura do arquivo");
	else
		printf("Texto: %s\n", str);
	
	fclose(fp);

	return 0;
}
