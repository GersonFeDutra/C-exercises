#include <stdio.h>
#include <locale.h>

#define MAX_CHARS 280


/* 6. Fa�a um programa que receba duas frases e, em seguida, crie uma string que conte-
nha as duas frases concatenadas. OBS: N�o pode usar as fun��es da biblioteca
<string.h> Ex.: Frase1: �L� vem o disco voador.� Frase2: �Se for dif�cil, ande mais de-
vagar.� � Frase Concatenada: �L� vem o disco voador.Se for dif�cil, ande mais devagar.�. */
int main()
{
	setlocale(LC_ALL, "Portuguese");
	char phrase1[MAX_CHARS + 1];
	char phrase2[MAX_CHARS + 1];
	char text[MAX_CHARS * 2 + 1];
	int i, length;
	length = i = 0;
	
	printf("Digite 2 frases abaixo (limite de %d caracters em cada frase)\n1�: ", MAX_CHARS);
	gets(phrase1);
	printf("\n2�: ");
	gets(phrase2);
	printf("\n");
	
	while (phrase1[i] != '\0') { // Note que n�o � poss�vel copiar caracteres acentuados corretamentes, sem importar uma biblioteca que lide com eles corretamente.
		text[i] = phrase1[i];
		++i;
	}
	
	if (i > 0) {
		length = i;
		i = 0;
	}
	
	while (phrase2[i] != '\0') {
		text[i + length] = phrase2[i];
		++i;
	}
	text[i + length] = '\0';
	
	printf("%s", text);
	
	return 0;
}

