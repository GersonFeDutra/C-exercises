#include <locale.h>

/* 3. Crie um procedimento (sem parâmetros) que receba do usuário (através do teclado) o
código da cidade, o nome e a temperatura em Celsius. A função deve retornar uma
estrutura do tipo cidade com os campos que foram digitados pelo usuário (use a função
da primeira questão para calcular o campo Fahrenheit).
struct cidade gera_cidade(); */
#include "ex03.h"


/* Usa a função `gera_cidade()` definida em "ex03.h" */
int main() {
	void print_cidade(struct cidade *c);
	setlocale(LC_ALL, "Portuguese");
	
	struct cidade c = gera_cidade();
	print_cidade(&c);
	
	return 0;
}

