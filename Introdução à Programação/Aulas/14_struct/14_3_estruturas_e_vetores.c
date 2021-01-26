#include <stdio.h>
#include <string.h>
#include <locale.h>


struct produto {
	char nome[20]; // A estrutura pode definir um array
	int qtd;
	float preco;
};



int main() {
	setlocale(LC_ALL, "Portuguese");

	int i;
	struct produto mercadorias[2]; // Array de estruturas
	//mercadorias[0] = {.qtd=20, .preco=1.99}; // Não sei pq essa declaração não está funcionando :C
	mercadorias[0].qtd = 20;
	mercadorias[0].preco = 1.99;
	//mercadorias[1] = {.qtd=2, .preco=5.35};
	mercadorias[1].qtd = 2;
	mercadorias[1].preco = 5.35;
	
	for (i = 0; i < 2; ++i) {
		printf("Quantidade de mercadorias %d: %d\n", i, mercadorias[i].qtd);
	}
	
	struct produto mercadoria;
	strcpy(mercadoria.nome, "Bomba atômica");
	mercadoria.qtd = 1;
	mercadoria.preco = 10.5;
	printf("Nome da mercadoria: %s\n", mercadoria.nome);

	return 0;
}
