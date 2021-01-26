#include <locale.h>

/* 2. Crie uma estrutura com nome "cidade". A estrutura deve conter os campos: Código da
cidade, nome da cidade, temperatura em Celsius da cidade e temperatura em Fahrenheit. */
#include "ex02.h"


/* Usa a estrutura `cidade` definida em "ex02.h" */
int main() {
	void print_cidade(struct cidade *c);
	float fahrenheit(float celsius);
	setlocale(LC_ALL, "Portuguese");
	
	struct cidade nova_cidade;
	printf("Insira os dados da cidade:\n");
	
	printf("Código: (inteiro) ");
	scanf("%d", &nova_cidade.codigo);
	while (getchar() != '\n');
	
	printf("Nome: ");
	gets(nova_cidade.nome);
	
	printf("Temperatura: °C ");
	scanf("%f", &nova_cidade.temperaturaC);
	
	nova_cidade.temperaturaF = fahrenheit(nova_cidade.temperaturaC);
	print_cidade(&nova_cidade);
	
	return 0;
}

