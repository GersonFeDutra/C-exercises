#include <locale.h>

/* 3. Crie um procedimento (sem par�metros) que receba do usu�rio (atrav�s do teclado) o
c�digo da cidade, o nome e a temperatura em Celsius. A fun��o deve retornar uma
estrutura do tipo cidade com os campos que foram digitados pelo usu�rio (use a fun��o
da primeira quest�o para calcular o campo Fahrenheit).
struct cidade gera_cidade(); */
#include "ex03.h"


/* Usa a fun��o `gera_cidade()` definida em "ex03.h" */
int main() {
	void print_cidade(struct cidade *c);
	setlocale(LC_ALL, "Portuguese");
	
	struct cidade c = gera_cidade();
	print_cidade(&c);
	
	return 0;
}

