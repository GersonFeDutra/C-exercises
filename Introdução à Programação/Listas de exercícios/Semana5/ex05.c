#include <stdio.h>
#include <locale.h>

#define MAX_CHARS 280

/* 5. Faça um programa que receba uma frase e dois caracteres. Depois verifique se o pri-
meiro caractere digitado aparece na frase digitada. Caso afirmativo, substitua todas as
aparições do primeiro caractere pela do segundo caractere. Por fim imprima a frase alte-
rada. (Considere letras maiúsculas e minúsculas como diferentes e considere que o usuário
não vai pedir para modificar letras acentuadas). Ex.: Frase: “Lá vem o disco voador”,
Caractere1: “o”, Caractere2: “w”- Frase Final: “Lá vem w discw vwadwr”. */
int main()
{
	setlocale(LC_ALL, "Portuguese");
	
	char phrase[MAX_CHARS + 1];
	char a, b;
	int i, hassubstring = 0;
	
	printf("Digite uma frase (até %d caracteres): ", MAX_CHARS);
	gets(phrase);
	
	printf("Insira dois caracters:\n");
	printf("Caractere1: ");
	scanf("%c", &a);
	
	while (getchar() != '\n'); // Impede que a entrada escape para o próximo scanf.
	
	printf("Caractere2: ");
	scanf("%c", &b);
	
	for (i = 0; phrase[i] != '\0'; ++i) {
		if (a == phrase[i]) {
			phrase[i] = b;
			hassubstring = 1;
		}
	}
	
	if (hassubstring)
		printf("\nSubstituindo %c por %c temos:\n>>> %s", a, b, phrase);
	else
		printf("\nO caractere '%c' não aparece na frase digitada.", a);
	
	return 0;
}

