#include <stdio.h>
#include <locale.h>


int main() {
	setlocale(LC_ALL, "Portuguese");
	
	int hours;
	float salary;
	printf("Quantas horas o funcion�rio trabalhou esse m�s? ");
	scanf("%d", &hours);
	printf("Quanto o funcion�rio recebe por hora? R$ ");
	scanf("%f", &salary);
	printf("O funcion�rio recebeu um total de R$ %.2f.", hours * salary);
	
	return 0;
}

