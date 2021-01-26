#include <stdio.h>
#include <locale.h>

struct dma {
	int dia;
	int mes;
	int ano;
};
struct ponto { // Tamb�m podemos criar estruturas em que os campos s�o ponteiros.
	int *x;
	int *y;
};


int main() {
	setlocale(LC_ALL, "Portuguese");

	struct dma data;
	struct dma *pd = &data;
	
	// H� duas formas de se acessar um campo de uma estrutura indicada por um ponteiro:
	(*pd).dia = 10;
	pd->mes = 10;
	printf("Dia: %d\n", pd->dia);
	printf("M�s: %d\n", (*pd).mes);
	
	struct ponto p;
	int i = 100, i2;
	p.x = &i;
	p.y = &i2;
	*p.y = -97;

	return 0;
}
