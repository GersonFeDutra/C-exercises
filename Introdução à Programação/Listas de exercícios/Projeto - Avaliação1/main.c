#include <stdio.h>
#include <locale.h>

// NOTA -> O sufixo `_RS` simboliza "preço"
#define TOMATO_RS 2.0 /* Preço do tomate. */
#define BANANA_RS 1.5 /* Preço da banana. */
#define APPLE_RS  1.0 /* Preço da maçã. */

#define LINE		"======================\n" /* Linha que cerca os cabeçalhos. */
#define SUCCESS 	"Operação realizada com sucesso.\n"		/* Mensagem de finalização de operação. */
#define TRY_AGAIN	"Entrada inválida! Tente novamente: "	/* Mensagem de erro de entrada. */
#define NO_STORAGE	"Operação inválida! Estoque insuficiente.\n" /* Mensagem de erro em venda de estoque. */


int main() {
	setlocale(LC_ALL, "Portuguese");
	
	/* Preços de vendas (dobro do preço de compra). */
	const float TOMATO_RS2 = 2 * TOMATO_RS;
	const float BANANA_RS2 = 2 * BANANA_RS;
	const float APPLE_RS2 = 2 * APPLE_RS;
	
	float money = 100.0, transaction;
	int bananas, tomatoes, apples, choice, qtd;
	bananas = tomatoes = apples = 0;
	
	while (1) {
		/* Tela inicial. */
		// Cabeçalho:
		printf(LINE);
		printf("   Caixa: R$%.2f\n", money);
		printf(LINE);
		printf("\n");
		// Opções:
		printf("1 - Comprar produtos.\n");
		printf("2 - Vender produtos.\n");
		printf("3 - Lista de produtos.\n");
		printf("4 - Sair.\n>>> ");
		scanf("%d", &choice);
		
		switch (choice) {
			case 1: { /* Comprar produtos. */
				// Opções:
				printf("\n====== COMPRAS =======\n");
				printf("1 - Tomate:\tR$%.2f\n", TOMATO_RS);
				printf("2 - Banana:\tR$%.2f\n", BANANA_RS);
				printf("3 - Maçã:\tR$%.2f\n", APPLE_RS);
				printf(LINE ">>> ");
				
				// Escolha entre opções de produtos, com validação de entrada:
				while (1) {
					scanf("%d", &choice);
					
					if (choice >= 1 && choice <= 3)
						break;
					else
						printf(TRY_AGAIN);
				} /* Decidi fazer a verificação com o `while`, pois torna o programa mais fácil de usar.
				(O usuário não terá que começar do zero caso digite um valor errado). De qualquer forma,
				basta remover o `while` e mudar a mensagem de saída no `else` para obter o mesmo compor-
				tamento apresentado pelo professor. Para cancelar a compra basta digitar uma quantidade
				nula ou	negativa na próxima entrada. O mesmo se aplica na tela de venda. */
				
				// Compra:
				printf("Quantos produtos você deseja comprar? ");
				scanf("%d", &qtd);
				
				// Verificação da compra. "Entrada nula ou negativa":
				if (qtd <= 0) {
					printf(LINE "  Operação cancelada.\n" LINE);
					break;
				}
				
				switch (choice) { // Calcula o preço da compra, de acordo com o produto.
					case 1: transaction = qtd * TOMATO_RS; break;
					case 2: transaction = qtd * BANANA_RS; break;
					case 3: transaction = qtd * APPLE_RS; break;
				}
				
				// Verificação da compra. "Crédito insuficiente":
				if (transaction > money) {
					printf(LINE "Operação inválida! Caixa insuficiente!\n" LINE);
					break;
				}
				
				// Aplicação da compra:
				money -= transaction;
				
				switch (choice) {
					case 1: tomatoes += qtd; break;
					case 2: bananas += qtd; break;
					case 3: apples += qtd; break;
				}
				
				printf(LINE "Compra realizada com sucesso!\n" LINE);
				break;
			}
			case 2: { /* Vender produtos. */
				printf("\n======= VENDAS =======\n");
				printf("1 - Tomate:\tR$%.2f\n", TOMATO_RS2);
				printf("2 - Banana:\tR$%.2f\n", BANANA_RS2);
				printf("3 - Maçã:\tR$%.2f\n", APPLE_RS2);
				printf(LINE ">>> ");
				
				// Escolha entre opções de produtos, com validação de entrada:
				while (1) {
					scanf("%d", &choice);
					
					if (choice >= 1 && choice <= 3)
						break;
					else
						printf(TRY_AGAIN);
				}
				
				// Venda:
				printf("Quantos produtos você deseja vender? ");
				scanf("%d", &qtd);
				
				// Verificação de venda. "Entrada nula ou negativa":
				if (qtd <= 0) {
					printf(LINE "  Operação cancelada.\n" LINE);
					break;
				}
				
				// Venda do produto.
				switch (choice) {
					case 1: { /* Tomates. */
						
						if (qtd > tomatoes) { // Verificação de estoque
							printf(LINE NO_STORAGE LINE);
						}
						else { // Aplicação da venda
							tomatoes -= qtd;
							money += qtd * TOMATO_RS2;
							printf(LINE SUCCESS LINE);
						}
						
						break;
					}
					case 2: { /* Bananas. */
						
						if (qtd > bananas) { // Verificação de estoque
							printf(LINE NO_STORAGE LINE);
						}
						else { // Aplicação da venda
							bananas -= qtd;
							money += qtd * BANANA_RS2;
							printf(LINE SUCCESS LINE);
						}
						
						break;
					}
					case 3: { /* Maçãs. */
						
						if (qtd > apples) { // Verificação de estoque
							printf(LINE NO_STORAGE LINE);
						}
						else { // Aplicação da venda
							apples -= qtd;
							money += qtd * APPLE_RS2;
							printf(LINE SUCCESS LINE);
						}
						
						break;
					}
				}
				
				break;
			}
			case 3: { /* Listar produtos. */
				printf("\n===== DESCRIÇÃO DOS PRODUTOS =====\n");
				printf("1 - Tomate - qtd: %2d\n", tomatoes);
				printf("2 - Banana - qtd: %2d\n", bananas);
				printf("3 - Maçã   - qtd: %2d\n", apples);
				printf("==================================\n");
				break;
			}
			case 4: { /* Sair. */
				return 0;
			}
			default: { // Ocorre quando o usuário digita uma entrada inválida.
				printf("%s\n", TRY_AGAIN);
				break;
			}
		}
		
		// Reseta saída do terminal
		system("pause");
		system("cls");
	}
}

