#include <stdio.h>
#include <locale.h>

#define MAX_CHARS 280


/* 7. Faça um programa que verifique se duas frases digitadas são iguais. OBS: Não pode
usar a biblioteca <string.h> */
int main()
{
	setlocale(LC_ALL, "Portuguese");
	char phrase1[MAX_CHARS + 1];
	char phrase2[MAX_CHARS + 1];
	int i, isequal = 1;
	
	printf("Digite 2 frases abaixo (limite de %d caracters em cada frase)\n1°: ", MAX_CHARS);
	gets(phrase1);
	printf("\n2°: ");
	gets(phrase2);
	printf("\n");
	
	for (i = 0; phrase1[i] != '\0'; ++i) {
		
		if (phrase1[i] != phrase2[i]) {
			isequal = 0;
			break;
		}
	}
	
	printf(isequal && phrase1[i] == phrase2[i] ? "As frases são iguais!" : "As frases são diferentes!");
	
	return 0;
}

