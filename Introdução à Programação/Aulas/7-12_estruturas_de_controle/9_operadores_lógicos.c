#include <stdio.h>
#include <locale.h>


int main() {
	void in_between(void), greetings(void), is_vowel(void), higher_then_10(void);
	
	setlocale(LC_ALL, "Portuguese");
	in_between();
	printf("\n");
	greetings();
	printf("\n");
	is_vowel();
	printf("\n");
	higher_then_10();
		
	return 0;
}


void in_between() {
	int number;
	
	printf("Digite um número inteiro: ");
	scanf("%d", &number);
	
	if (number >= 20 && number <= 90) {
		printf("%d está entre 20 e 90.\n", number);
	}
	else {
		printf("%d não está entre 20 e 90.\n", number);
	}
}


void greetings() {
	int hours;
	
	printf("Que horas são? ");
	scanf("%d", &hours);
	
	// Verificação apenas para não lidar com tratamento de entrada.
	if (!(hours >= 0 && hours <= 24)) {
		return;
	}
	
	if (hours > 3 && hours < 12) {
		printf("Bom dia!\n");
	}
	else if (hours >= 12 && hours < 18) {
		printf("Boa tarde!\n");
	}
	else {
		printf("Boa noite!\n");
	}
}


void is_vowel() {
	char c;
	
	printf("Digite uma letra: ");
	scanf("%s", &c);
	
	// TODO -> Importar método que muda a caixa de caracteres.
	if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
		printf("%c é vogal!\n", c);
	}
	else {
		printf("%c não é vogal!\n", c);
	}
}


void higher_then_10() {
	int value;
	
	printf("Digite um número inteiro: ");
	scanf("%d", &value);
	
	if (!(value >= 10)) {
		printf("Valor menor que 10.");
	}
	else {
		printf("Valor maior ou igual a 10");
	}
}

