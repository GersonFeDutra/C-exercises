#include <stdio.h>
#include <locale.h>

// NOTA -> O sufixo `_RS` simboliza "pre�o"
#define TOMATO_RS 2.0 /* Pre�o do tomate. */
#define BANANA_RS 1.5 /* Pre�o da banana. */
#define APPLE_RS  1.0 /* Pre�o da ma��. */

#define LINE		"======================\n" /* Linha que cerca os cabe�alhos. */
#define SUCCESS 	"Opera��o realizada com sucesso.\n"		/* Mensagem de finaliza��o de opera��o. */
#define TRY_AGAIN	"Entrada inv�lida! Tente novamente: "	/* Mensagem de erro de entrada. */
#define NO_STORAGE	"Opera��o inv�lida! Estoque insuficiente.\n" /* Mensagem de erro em venda de estoque. */


int main() {
	setlocale(LC_ALL, "Portuguese");
	
	/* Pre�os de vendas (dobro do pre�o de compra). */
	const float TOMATO_RS2 = 2 * TOMATO_RS;
	const float BANANA_RS2 = 2 * BANANA_RS;
	const float APPLE_RS2 = 2 * APPLE_RS;
	
	float money = 100.0, transaction;
	int bananas, tomatoes, apples, choice, qtd;
	bananas = tomatoes = apples = 0;
	
	while (1) {
		/* Tela inicial. */
		// Cabe�alho:
		printf(LINE);
		printf("   Caixa: R$%.2f\n", money);
		printf(LINE);
		printf("\n");
		// Op��es:
		printf("1 - Comprar produtos.\n");
		printf("2 - Vender produtos.\n");
		printf("3 - Lista de produtos.\n");
		printf("4 - Sair.\n>>> ");
		scanf("%d", &choice);
		
		switch (choice) {
			case 1: { /* Comprar produtos. */
				// Op��es:
				printf("\n====== COMPRAS =======\n");
				printf("1 - Tomate:\tR$%.2f\n", TOMATO_RS);
				printf("2 - Banana:\tR$%.2f\n", BANANA_RS);
				printf("3 - Ma��:\tR$%.2f\n", APPLE_RS);
				printf(LINE ">>> ");
				
				// Escolha entre op��es de produtos, com valida��o de entrada:
				while (1) {
					scanf("%d", &choice);
					
					if (choice >= 1 && choice <= 3)
						break;
					else
						printf(TRY_AGAIN);
				} /* Decidi fazer a verifica��o com o `while`, pois torna o programa mais f�cil de usar.
				(O usu�rio n�o ter� que come�ar do zero caso digite um valor errado). De qualquer forma,
				basta remover o `while` e mudar a mensagem de sa�da no `else` para obter o mesmo compor-
				tamento apresentado pelo professor. Para cancelar a compra basta digitar uma quantidade
				nula ou	negativa na pr�xima entrada. O mesmo se aplica na tela de venda. */
				
				// Compra:
				printf("Quantos produtos voc� deseja comprar? ");
				scanf("%d", &qtd);
				
				// Verifica��o da compra. "Entrada nula ou negativa":
				if (qtd <= 0) {
					printf(LINE "  Opera��o cancelada.\n" LINE);
					break;
				}
				
				switch (choice) { // Calcula o pre�o da compra, de acordo com o produto.
					case 1: transaction = qtd * TOMATO_RS; break;
					case 2: transaction = qtd * BANANA_RS; break;
					case 3: transaction = qtd * APPLE_RS; break;
				}
				
				// Verifica��o da compra. "Cr�dito insuficiente":
				if (transaction > money) {
					printf(LINE "Opera��o inv�lida! Caixa insuficiente!\n" LINE);
					break;
				}
				
				// Aplica��o da compra:
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
				printf("3 - Ma��:\tR$%.2f\n", APPLE_RS2);
				printf(LINE ">>> ");
				
				// Escolha entre op��es de produtos, com valida��o de entrada:
				while (1) {
					scanf("%d", &choice);
					
					if (choice >= 1 && choice <= 3)
						break;
					else
						printf(TRY_AGAIN);
				}
				
				// Venda:
				printf("Quantos produtos voc� deseja vender? ");
				scanf("%d", &qtd);
				
				// Verifica��o de venda. "Entrada nula ou negativa":
				if (qtd <= 0) {
					printf(LINE "  Opera��o cancelada.\n" LINE);
					break;
				}
				
				// Venda do produto.
				switch (choice) {
					case 1: { /* Tomates. */
						
						if (qtd > tomatoes) { // Verifica��o de estoque
							printf(LINE NO_STORAGE LINE);
						}
						else { // Aplica��o da venda
							tomatoes -= qtd;
							money += qtd * TOMATO_RS2;
							printf(LINE SUCCESS LINE);
						}
						
						break;
					}
					case 2: { /* Bananas. */
						
						if (qtd > bananas) { // Verifica��o de estoque
							printf(LINE NO_STORAGE LINE);
						}
						else { // Aplica��o da venda
							bananas -= qtd;
							money += qtd * BANANA_RS2;
							printf(LINE SUCCESS LINE);
						}
						
						break;
					}
					case 3: { /* Ma��s. */
						
						if (qtd > apples) { // Verifica��o de estoque
							printf(LINE NO_STORAGE LINE);
						}
						else { // Aplica��o da venda
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
				printf("\n===== DESCRI��O DOS PRODUTOS =====\n");
				printf("1 - Tomate - qtd: %2d\n", tomatoes);
				printf("2 - Banana - qtd: %2d\n", bananas);
				printf("3 - Ma��   - qtd: %2d\n", apples);
				printf("==================================\n");
				break;
			}
			case 4: { /* Sair. */
				return 0;
			}
			default: { // Ocorre quando o usu�rio digita uma entrada inv�lida.
				printf("%s\n", TRY_AGAIN);
				break;
			}
		}
		
		// Reseta sa�da do terminal
		system("pause");
		system("cls");
	}
}

