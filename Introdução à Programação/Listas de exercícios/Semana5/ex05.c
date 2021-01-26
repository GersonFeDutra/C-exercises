#include <stdio.h>
#include <locale.h>

#define MAX_CHARS 280

/* 5. Fa�a um programa que receba uma frase e dois caracteres. Depois verifique se o pri-
meiro caractere digitado aparece na frase digitada. Caso afirmativo, substitua todas as
apari��es do primeiro caractere pela do segundo caractere. Por fim imprima a frase alte-
rada. (Considere letras mai�sculas e min�sculas como diferentes e considere que o usu�rio
n�o vai pedir para modificar letras acentuadas). Ex.: Frase: �L� vem o disco voador�,
Caractere1: �o�, Caractere2: �w�- Frase Final: �L� vem w discw vwadwr�. */
int main()
{
	setlocale(LC_ALL, "Portuguese");
	
	char phrase[MAX_CHARS + 1];
	char a, b;
	int i, hassubstring = 0;
	
	printf("Digite uma frase (at� %d caracteres): ", MAX_CHARS);
	gets(phrase);
	
	printf("Insira dois caracters:\n");
	printf("Caractere1: ");
	scanf("%c", &a);
	
	while (getchar() != '\n'); // Impede que a entrada escape para o pr�ximo scanf.
	
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
		printf("\nO caractere '%c' n�o aparece na frase digitada.", a);
	
	return 0;
}

