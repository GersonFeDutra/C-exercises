#include <stdio.h>
#include <locale.h>

struct dm {
	int dia;
	int mes;
};


// Note que essa passagem ocorre por valor, logo pode não ser muito eficiênte
int mesmo_dia(struct dm data1, struct dm data2) {
	return data1.dia == data2.dia;
}

// Passagem por referência
void incrementa_dia(struct dm *data) {
	(*data).dia++;
}

// Retorna uma estrutura
struct dm gera_dm() {
	struct dm novo;
	
	printf("Digite o dia: ");
	scanf("%d", &novo.dia);
	
	printf("Digite o mês: ");
	scanf("%d", &novo.mes);
	
	return novo;
}

int main() {
	setlocale(LC_ALL, "Portuguese");
	
	struct dm dataa = {.dia=1, .mes=3};
	struct dm datab = gera_dm();
	printf("Mesmo dia? %c\n", mesmo_dia(dataa, datab) ? 's' : 'n');
	
	incrementa_dia(&datab);
	printf("Nova data: %d/%d\n", datab.dia, datab.mes);

	return 0;
}
