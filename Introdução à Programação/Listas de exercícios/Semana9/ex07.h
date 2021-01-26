#include "ex06.h"  // structs: cidade / funções: fahrenheit(), print_cidade(), gera_cidade()


/* 7. Crie um procedimento com nome altera_temperatura que tem como parâmetros uma
estrutura do tipo cidade e um número real (pode ser negativo) que é a quantidade de
unidades em Celsius que será incrementado (ou decrementado) da temperatura da cidade.
Após atualizar a temperatura em Celsius, atualize a temperatura em Fahrenheit também
(usando a função da primeira questão).
void altera_temperatura(struct cidade *cid, float numero); */
void altera_temperatura(struct cidade *cid, float numero) {
	float fahrenheit(float celsius);
	
	cid->temperaturaC += numero;
	cid->temperaturaF = fahrenheit(cid->temperaturaC);
}

