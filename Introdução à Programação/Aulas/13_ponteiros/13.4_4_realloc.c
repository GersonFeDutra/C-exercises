#include <stdlib.h>


int main() {
	int *p = (int*)malloc(2*sizeof(int));

	*p = 10; // Armazena o valor 10 na primeira região.
	*(p + 1) = 20; // Armazena o valor 20 na segunda região.
	
	int *p_novo = (int*)realloc(p, 4*sizeof(int));
	
	printf("%d\n", *p_novo); // imprime 10.
	printf("%d\n", *(p_novo + 1)); // imprime 20.

	return 0;
}
