#include <stdio.h>
#include <locale.h>


int main() {
	setlocale(LC_ALL, "Portuguese");

	FILE *arquivo;
	arquivo = fopen("meu_arquivo.txt", "w");
	
	if (arquivo == NULL) {
		printf("Ocorreu um erro de abertura do arquivo.\n");
		return -1;
	}
	
	printf("Arquivo criado com sucesso!\n");
	fclose(arquivo);

	return 0;
}
