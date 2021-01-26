#include <stdlib.h>


int main() {
	int *p = (int*)malloc(3*sizeof(int));

	*p = 1; // Armazena o valor 1 na primeira região.
	*(p + 1) = 2; // Armazena o valor 2 na segunda região.
	*(p + 2) = 3; // Armazena o valor 3 na terceira região.
	
	printf("%d\n", *p); // imprime 1.
	printf("%d\n", *(p + 1)); // imprime 2.
	
	p[0] = 4; // Armazena o valor 1 na primeira regi˜ao.
	p[1] = 5; // Armazena o valor 2 na segunda regi˜ao.
	p[2] = 6; // Armazena o valor 3 na terceira regi˜ao.
	
	printf("%d \n", p[0]); // imprime 4.
	printf("%d \n", p[1]); // imprime 5.

	return 0;
}
