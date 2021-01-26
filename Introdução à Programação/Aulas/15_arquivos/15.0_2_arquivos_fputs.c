#include <stdio.h>


int main() {
	FILE *fp;
	fp = fopen("escrita.txt", "w");
	
	if (fp == NULL) {
		printf("Erro ao abrir o arquivo");
		return -1;
	}
	
	char texto[] = "Meu programa em C.\n";
	// Grava toda a string no arquivo.
	int retorno = fputs(texto, fp);
	
	if (retorno == EOF)
		printf("Erro na gravação do arquivo.");
	
	fputs("Teste!", fp);
	fclose(fp);

	return 0;
}
