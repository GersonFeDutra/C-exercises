#include <stdio.h>
#include <locale.h>


int main() {
	setlocale(LC_ALL, "Portuguese");
	
	float salary, taxes, syndicated;
	printf("Quanto voc� ganha por m�s? R$ ");
	scanf("%f", &salary);
	taxes = salary * 0.08;
	syndicated = salary * 0.05;
	printf("\n");
	printf("Sal�rio bruto: R$ %.2f ao m�s, R$ %.2f ao ano.\n", salary, salary * 12);
	printf("Impostos aplicados (8%% do sal�rio): R$ %.2f.\n", taxes);
	printf("Valor pago ao sindicato: (5%% do sal�rio): R$ %.2f.\n", syndicated);
	printf("Sal�rio l�quido: R$ %.2f.", salary - (taxes + syndicated) );
	return 0;
}

