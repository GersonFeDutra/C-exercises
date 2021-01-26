#include <stdio.h>
#include <locale.h>


/* Escreva um algoritmo que imprime os três primeiros múltiplos de 3 */
int main() {
	setlocale(LC_ALL, "Portuguese");
	
	int i;
	printf("Os múltiplos de 3 são: ");
	
	for (i = 1; i <= 10; ++i)
		printf("%d ", i * 3);
	
	return 0;
}

