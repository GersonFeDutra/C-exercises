#include "ex01.h" // fahrenheit()


/* 2. Crie uma estrutura com nome "cidade". A estrutura deve conter os campos: Código da
cidade, nome da cidade, temperatura em Celsius da cidade e temperatura em Fahrenheit. */
struct cidade {
	int codigo;
	char nome[20];
	float temperaturaC;
	float temperaturaF;
};

/* Imprime os dados da estrutura "cidade". */
void print_cidade(struct cidade *c) {
	printf(
			"A cidade %s de código %d tem temperatura média de %.1f°C / %.1f°F.\n",
			c->nome, c->codigo, c->temperaturaC, c->temperaturaF
	);
}

