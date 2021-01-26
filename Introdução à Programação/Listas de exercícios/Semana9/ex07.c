#include <locale.h>

/* 7. Crie um procedimento com nome altera_temperatura que tem como par�metros uma
estrutura do tipo cidade e um n�mero real (pode ser negativo) que � a quantidade de
unidades em Celsius que ser� incrementado (ou decrementado) da temperatura da cidade.
Ap�s atualizar a temperatura em Celsius, atualize a temperatura em Fahrenheit tamb�m
(usando a fun��o da primeira quest�o).
void altera_temperatura(struct cidade *cid, float numero); */
#include "ex07.h"


/* Usa a fun��o `altera_temperatura()` definida em "ex07.h" */
int main() {
	void altera_temperatura(struct cidade *cid, float numero);
	void print_cidade(struct cidade *c);
	setlocale(LC_ALL, "Portuguese");
	
	int i;
	struct cidade c = gera_cidade();
	printf("\nAntes:\n");
	print_cidade(&c);
	
	altera_temperatura(&c, 10);
	printf("\nAp�s alterar a mudan�a de temperatura:\n");
	print_cidade(&c);
	
	return 0;
}

