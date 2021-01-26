#include <stdio.h>


int main() {
	int a[5] = {8, 2, 4, 9, 5};
	int *p = a; // Equivale � *p = &a[0]`
	
	printf("%d\n", *p); // Imprime 8
	printf("%d\n", *(p + 1)); // Imprime 2
	printf("%d\n", *(p + 2)); // Imprime 4
	printf("%d\n", (p + 2)); // Imprime endere�o &a[2]
	
	++p;
	printf("%d\n", *p); // Imprime 2
	printf("%d\n", *(p + 1)); // Imprime 4
	printf("%d\n", *(p - 1)); // Imprime 8
	printf("%d\n", (p + 2)); // Imprime endere�o &a[3]
	
	printf("%d\n", sizeof(int)); // Diferen�a entre &a[3] - &a[2]

	return 0;
}
