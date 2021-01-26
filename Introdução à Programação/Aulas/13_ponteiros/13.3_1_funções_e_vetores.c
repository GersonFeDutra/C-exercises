#include <stdio.h>


int incrementa_vect(int vet[], int tam) {
	int i;
	
	for (i = 0; i < tam; ++i)
		++vet[i]; // Vetores são passados por referência.
}

int incrementa_point(int *vet, int tam) {
	int i;
	
	for (i = 0; i < tam; ++i)
		++*(vet + i); // `*(vet + i)` equivale à `vet[i]`
}

int main() {
	int i;
	int a[] = {1, 2, 3, 4, 5};
	
	incrementa_vect(a, 5);
	
	for (i = 0; i < 5; ++i) {
		printf("%d\n", a[i]);
	}
	
	printf("\n");
	incrementa_point(a, 5); // `a` equivale à &a[0]
	
	for (i = 0; i < 5; ++i) {
		printf("%d\n", a[i]);
	}

	return 0;
}
