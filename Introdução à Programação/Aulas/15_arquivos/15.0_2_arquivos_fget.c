#include <stdio.h>


int main() {
	FILE *fp;
	int c;
	
	fp = fopen("arquivo.txt", "r");
	
	if (fp == NULL) {
		printf("Erro na abertura do arquivo!");
		return -1;
	}
	
	c = fgetc(fp);
	
	while (c != EOF) {
		printf("%c", c);
		c = fgetc(fp);
	}
	
	fclose(fp);

	return 0;
}
