#include <stdio.h>
#include <locale.h>


int main() {
	setlocale(LC_ALL, "Portuguese");
	
	float salary, taxes, syndicated;
	printf("Quanto você ganha por mês? R$ ");
	scanf("%f", &salary);
	taxes = salary * 0.08;
	syndicated = salary * 0.05;
	printf("\n");
	printf("Salário bruto: R$ %.2f ao mês, R$ %.2f ao ano.\n", salary, salary * 12);
	printf("Impostos aplicados (8%% do salário): R$ %.2f.\n", taxes);
	printf("Valor pago ao sindicato: (5%% do salário): R$ %.2f.\n", syndicated);
	printf("Salário líquido: R$ %.2f.", salary - (taxes + syndicated) );
	return 0;
}

