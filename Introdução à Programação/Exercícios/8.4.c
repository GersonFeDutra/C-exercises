#include <stdio.h>
#include <locale.h>


/* Escreva um algoritmo que imprime os tr�s primeiros m�ltiplos de 3 */
int main() {
	setlocale(LC_ALL, "Portuguese");
	
	int i;
	printf("Os m�ltiplos de 3 s�o: ");
	
	for (i = 1; i <= 10; ++i)
		printf("%d ", i * 3);
	
	return 0;
}

