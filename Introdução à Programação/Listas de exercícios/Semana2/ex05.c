#include <stdio.h>
#include <locale.h>


int main() {
	setlocale(LC_ALL, "Portuguese");
	
	int hours;
	float salary;
	printf("Quantas horas o funcionário trabalhou esse mês? ");
	scanf("%d", &hours);
	printf("Quanto o funcionário recebe por hora? R$ ");
	scanf("%f", &salary);
	printf("O funcionário recebeu um total de R$ %.2f.", hours * salary);
	
	return 0;
}

