#include <stdio.h>


int main() {
	int *p = (int*)calloc(2, sizeof(int));

	*p = 10; // Armazena o valor 10 na primeira regi�o.
	*(p + 1) = 20; // Armazena o valor 20 na segunda regi�o.
	
	printf("%d \n", *p); // imprime 10.
	printf("%d \n", *(p + 1)); // imprime 20.

	return 0;
}
