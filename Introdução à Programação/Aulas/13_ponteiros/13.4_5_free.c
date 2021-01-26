#include <stdlib.h>


int main() {
	int *p = (int*)malloc(2*sizeof(int));

	*p = 10; // Armazena o valor 10 na primeira regi�o.
	*(p + 1) = 20; // Armazena o valor 20 na segunda regi�o.
	
	printf("%d\n", *p); // imprime 10.
	printf("%d\n", *(p + 1)); // imprime 20.
	
	free(p); // Libera regi�o alocada.
	p = NULL; // Ajusta o ponteiro para NULL.

	return 0;
}
