#include <stdio.h>
#include <locale.h>


int soma_dos_elementos(int vet[], int tam) {
	int soma = 0, i;

	for (i = 0; i < tam; ++i) {
		soma += vet[i];
	}

	return soma;
}

int main() {
	setlocale(LC_ALL, "Portuguese");

	int a[] = {1, 2, 3, 4, 5};
	printf("Soma: %d\n", soma_dos_elementos(a, 5));

	return 0;
}
