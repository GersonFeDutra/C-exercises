#include <stdio.h>

#define ENTRIES 5


int main() {
	FILE *fp;
	// Abre arquivo em modo de leitura binária.
	fp = fopen("vetor.txt", "rb");
	
	if (fp == NULL) {
		printf("Erro ao abrir o arquivo");
		return -1;
	}
	
	int total_lido, v[ENTRIES], i;
	total_lido = fread(v, sizeof(int), ENTRIES, fp);
	
	if (total_lido != ENTRIES)
		printf("Erro na leitura do arquivo.");
	
	for (i = 0; i < ENTRIES; ++i)
		printf("%d ", v[i]);
	
	fclose(fp);

	return 0;
}
