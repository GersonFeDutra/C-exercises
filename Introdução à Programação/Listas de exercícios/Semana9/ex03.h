#include "ex02.h"  // structs: cidade / fun��es: fahrenheit(), print_cidade()


/* 3. Crie um procedimento (sem par�metros) que receba do usu�rio (atrav�s do teclado) o
c�digo da cidade, o nome e a temperatura em Celsius. A fun��o deve retornar uma
estrutura do tipo cidade com os campos que foram digitados pelo usu�rio (use a fun��o
da primeira quest�o para calcular o campo Fahrenheit).
struct cidade gera_cidade(); */
struct cidade gera_cidade() {
	float fahrenheit(float celsius);
	
	struct cidade nova_cidade;
	printf("Insira os dados da cidade:\n");
	
	printf("C�digo: (inteiro) ");
	scanf("%d", &nova_cidade.codigo);
	while (getchar() != '\n');
	
	printf("Nome: ");
	
	while (1) {
		gets(nova_cidade.nome);
	
		if (nova_cidade.nome[0] == '-')
			printf("O nome da cidade n�o pode come�ar com '-'.\nPor favor, tente novamente: ");
		else
			break;
	}
	
	printf("Temperatura: �C ");
	scanf("%f", &nova_cidade.temperaturaC);
	
	nova_cidade.temperaturaF = fahrenheit(nova_cidade.temperaturaC);
	
	return nova_cidade;
}

