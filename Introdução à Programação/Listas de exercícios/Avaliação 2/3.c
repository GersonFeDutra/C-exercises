#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define FALSE 0
#define TRUE 1
#define QTD 6

struct Cliente {
	int codigo;
	float saldo;
	int genero;
};


/* 3. Crie uma struct que represente o cliente de um banco (struct Cliente). O struct deve
conter os campos: int codigo, float saldo (o saldo pode ser negativo, caso o cliente esteja
com dívidas) e int genero (0 para masculino e 1 para feminino). No programa principal,
aloque 6 posições na memória Heap do tipo struct Cliente e forneça valores para eles.
Eles representarão os clientes do banco. Dado esse contexto:
(a) Crie uma função que retorne a média do saldo dos clientes do banco de determinado
gênero. Por exemplo, se for passado 0 como argumento de gênero, a função deverá
retornar a média dos salários dos clientes masculinos. A assinatura da função é dada
por: float media(struct Cliente* vet, int tam, int genero); (2.0)
(b) Crie uma função que tenha gênero como um de seus parâmetros. A função deve
retornar o endereço da memória com o cliente daquele gênero com maior saldo no
banco. Por exemplo, para gênero = 1, a função deve retornar o endereço do cliente
que tem o maior saldo entre as mulheres. A assinatura da função é dada por: struct
Cliente* maior_por_genero(struct Cliente* vet, int tam, int genero); (2.0) */
int main() {
	float media_genero(struct Cliente* vet, int tam, int genero);
	struct Cliente* maior_por_genero(struct Cliente* vet, int tam, int genero);
	setlocale(LC_ALL, "Portuguese");

	struct Cliente* clientes = (struct Cliente*)calloc(QTD, sizeof(struct Cliente));
	int i;

	for (i = 0; i < QTD; ++i) {
		printf("Insira os dados do %d° cliente:\n", i + 1);
		clientes[i].codigo = i;
		printf("Saldo: ");
		scanf("%f", &clientes[i].saldo);
		
		while (TRUE) {
			printf("Gênero (0 - masculino, 1 - feminino): ");
			scanf("%d", &clientes[i].genero);
			
			if (clientes[i].genero == 0 || clientes[i].genero == 1)
				break;
			
			printf("Erro de entrada, por favor, insira um valor válido:\n");
		}
		printf("\n");
	}
	
	printf("\n");
	printf("A média dos clientes do sexo masculino é: %.2f\n", media_genero(clientes, QTD, 0));
	printf("A média dos clientes do sexo feminino é: %.2f\n", media_genero(clientes, QTD, 1));
	
	{
		struct Cliente* cliente_maior_saldo = maior_por_genero(clientes, QTD, 0);
		
		printf(
			"O cliente do sexo masculino de maior saldo tem código %d, com um total de %.2f.\n",
			cliente_maior_saldo->codigo, cliente_maior_saldo->saldo
		);
		
		cliente_maior_saldo = maior_por_genero(clientes, QTD, 1);
		printf(
			"O cliente do sexo feminino de maior saldo tem código %d, com um total de %.2f\n.",
			cliente_maior_saldo->codigo, cliente_maior_saldo->saldo
		);
	}
	
	// for (i = 0; i < QTD; ++i) {
	// 	printf("\n");
	// 	printf("%d° cliente:\n", i + 1);
	// 	printf("Código: %d\n", clientes[i].codigo);
	// 	printf("Saldo: %.2f\n", clientes[i].saldo);
	// 	printf("Gênero: %s\n", clientes[i].genero ? "Feminino" : "Masculino");
	// }

	return 0;
}


float media_genero(struct Cliente* vet, int tam, int genero) {
	float counter = 0;
	int i;

	for (i = 0; i < tam; ++i) {

		if (vet[i].genero == genero)
			counter += vet[i].saldo;
	}

	return counter / (float)tam;
}

struct Cliente* maior_por_genero(struct Cliente* vet, int tam, int genero) {
	struct Cliente* cliente = &vet[0];
	int i;

	for (i = 1; i < tam; ++i) {

		if (vet[i].genero == genero && vet[i].saldo > cliente->saldo)
			cliente = &vet[i];
	}

	return cliente;
}
