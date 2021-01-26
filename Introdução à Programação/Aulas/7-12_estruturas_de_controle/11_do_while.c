#include <stdio.h>
#include <locale.h>


int main() {
	setlocale(LC_ALL, "Portuguese");
	
	int cont = 1, soma = 0;
	
	do {
		soma += cont;
		++cont;
	}
	while (cont <= 5);
	
	printf("Soma dos 5 primeiros números naturais: %d", soma);
	
	return 0;
}

