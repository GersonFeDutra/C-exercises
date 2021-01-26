#include "ex02.h"  // structs: cidade / funções: fahrenheit(), print_cidade()


/* 3. Crie um procedimento (sem parâmetros) que receba do usuário (através do teclado) o
código da cidade, o nome e a temperatura em Celsius. A função deve retornar uma
estrutura do tipo cidade com os campos que foram digitados pelo usuário (use a função
da primeira questão para calcular o campo Fahrenheit).
struct cidade gera_cidade(); */
struct cidade gera_cidade() {
	float fahrenheit(float celsius);
	
	struct cidade nova_cidade;
	printf("Insira os dados da cidade:\n");
	
	printf("Código: (inteiro) ");
	scanf("%d", &nova_cidade.codigo);
	while (getchar() != '\n');
	
	printf("Nome: ");
	
	while (1) {
		gets(nova_cidade.nome);
	
		if (nova_cidade.nome[0] == '-')
			printf("O nome da cidade não pode começar com '-'.\nPor favor, tente novamente: ");
		else
			break;
	}
	
	printf("Temperatura: °C ");
	scanf("%f", &nova_cidade.temperaturaC);
	
	nova_cidade.temperaturaF = fahrenheit(nova_cidade.temperaturaC);
	
	return nova_cidade;
}

