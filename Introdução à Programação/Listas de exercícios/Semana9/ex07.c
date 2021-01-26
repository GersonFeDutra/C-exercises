#include <locale.h>

/* 7. Crie um procedimento com nome altera_temperatura que tem como parâmetros uma
estrutura do tipo cidade e um número real (pode ser negativo) que é a quantidade de
unidades em Celsius que será incrementado (ou decrementado) da temperatura da cidade.
Após atualizar a temperatura em Celsius, atualize a temperatura em Fahrenheit também
(usando a função da primeira questão).
void altera_temperatura(struct cidade *cid, float numero); */
#include "ex07.h"


/* Usa a função `altera_temperatura()` definida em "ex07.h" */
int main() {
	void altera_temperatura(struct cidade *cid, float numero);
	void print_cidade(struct cidade *c);
	setlocale(LC_ALL, "Portuguese");
	
	int i;
	struct cidade c = gera_cidade();
	printf("\nAntes:\n");
	print_cidade(&c);
	
	altera_temperatura(&c, 10);
	printf("\nApós alterar a mudança de temperatura:\n");
	print_cidade(&c);
	
	return 0;
}

