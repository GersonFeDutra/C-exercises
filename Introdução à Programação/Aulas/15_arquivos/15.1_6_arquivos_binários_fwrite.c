#include <stdio.h>


int main() {
	FILE *fp;
	fp = fopen("vetor.txt", "wb");
	
	if (fp == NULL) {
		printf("Erro ao abrir o arquivo");
		return -1;
	}
	
	int vetor[5] = {1, 2, 3, 4, 5};
	int total_gravado = fwrite(vetor, sizeof(int), 5, fp);
	
	if (total_gravado != 5)
		printf("Não foram gravados todos os inteiros");
	
	fclose(fp);

	return 0;
}
