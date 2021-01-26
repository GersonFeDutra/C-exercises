#include <stdio.h>
#include <locale.h>


int main() {
	void product_price(void), natural_number_check(void), operations(void), energy_cost(void);
	setlocale(LC_ALL, "Portuguese");
	
	product_price();
	printf("\n");
	natural_number_check();
	printf("\n");
	operations();
	printf("\n");
	energy_cost();
	
	return 0;
}


void product_price() {
	int category;
	float price = 0;
	
	printf("Digite uma categoria de produto: (1-5) ");
	scanf("%d", &category);
	
	switch (category) {
		case 1: price = 10; break;
		case 2: price = 18; break;
		case 3: price = 23; break;
		case 4: price = 26; break;
		case 5: price = 31; break;
		default: printf("Categoria inexistente.\n");
	}
	
	printf("O preço do produto é R$ %.2f.\n", price);
}


void natural_number_check() {
	int n;
	printf("Digite um número inteiro: ");
	scanf("%d", &n);
	
	if (n > 0) {
		printf("Positivo.\n");
	}
	else if (n < 0) {
		printf("Negativo.\n");
	}
	else {
		printf("Nulo.\n");
	}
}


void operations() {
	int choice;
	float a, b;
	
	printf("Digite um valor numérico para a: ");
	scanf("%f", &a);
	printf("Digite um valor numérico para b: ");
	scanf("%f", &b);
	printf("Que tipo de operação deseja fazer?\n1 - Soma\n2 - Subtração\n3 - Multiplicação\n4 - Divisão\n");
	scanf("%d", &choice);
	
	switch (choice) {
		case 1: printf("a + b = %.1f\n", a + b); break;
		case 2: printf("a - b = %.1f\n", a - b); break;
		case 3: printf("a * b = %.1f\n", a * b); break;
		case 4: printf("a / b = %.1f\n", a / b); break;
		default: printf("Opção inexistente!\n");
	}
}


void energy_cost() {
	char edification;
	float energy, price;
	
	printf("Quanto de energia elétrica foi consumida? (kWh) ");
	scanf("%f", &energy);
	printf("Qual o tipo de instalação da edificação?\nR - Residência\nI - Indústria\nC - Comércio\n");
	scanf("%s", &edification);
	
	switch (edification) {
		case 'R': {
			if (energy <= 500) {
				price = 0.4 ;
			}
			else {
				price = 0.65;
			}
			break;
		}
		case 'I': {
			if (energy <= 1000) {
				price = 0.55;
			} else {
				price = 0.6;
			}
			break;
		}
		case 'C': {
			if (energy <= 5000) {
				price = 0.55;
			}
			else {
				price = 0.6;
			}
			break;
		}
		default: printf("Essa não é uma opção válida!\n");
	}
	printf("O custo da energia será de R$ %.2f.", energy * price);
}

