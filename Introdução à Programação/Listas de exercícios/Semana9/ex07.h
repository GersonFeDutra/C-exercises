#include "ex06.h"  // structs: cidade / fun��es: fahrenheit(), print_cidade(), gera_cidade()


/* 7. Crie um procedimento com nome altera_temperatura que tem como par�metros uma
estrutura do tipo cidade e um n�mero real (pode ser negativo) que � a quantidade de
unidades em Celsius que ser� incrementado (ou decrementado) da temperatura da cidade.
Ap�s atualizar a temperatura em Celsius, atualize a temperatura em Fahrenheit tamb�m
(usando a fun��o da primeira quest�o).
void altera_temperatura(struct cidade *cid, float numero); */
void altera_temperatura(struct cidade *cid, float numero) {
	float fahrenheit(float celsius);
	
	cid->temperaturaC += numero;
	cid->temperaturaF = fahrenheit(cid->temperaturaC);
}

