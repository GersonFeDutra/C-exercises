#include <stdio.h>
#include <locale.h>


int main() {
	setlocale(LC_ALL, "Portuguese");
	
	int i, soma = 0;
	
	for (i = 1; i <= 5; ++i)
		soma += i;
	
	printf("A soma dos 5 primeiros números naturais é: %d", soma);
	
	return 0;
}

