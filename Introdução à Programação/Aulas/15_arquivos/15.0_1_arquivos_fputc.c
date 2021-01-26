#include <stdio.h>


int main() {
	FILE *pont_arq;
	int c;
	
	pont_arq = fopen("escrita.txt", "w");
	
	if (pont_arq == NULL) {
		printf("Erro na abertura do arquivo!");
		return -1;
	}
	
	char texto[] = "O rato roeu a roupa do rei de roma.";
	int i = 0;
	
	while (texto[i] != '\0') {
		fputc(texto[i], pont_arq);
		i++;
	}
	
	fclose(pont_arq);

	return 0;
}
