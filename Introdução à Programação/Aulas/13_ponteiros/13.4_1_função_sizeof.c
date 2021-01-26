#include <stdio.h>
#include <locale.h>


int main() {
	setlocale(LC_ALL, "Portuguese");

	int a = 25;
	printf("Espaço alocado para...\n");
	printf("variável a: %d\n", sizeof a);
	printf("int: %d\n", sizeof(int));
	printf("char: %d\n", sizeof(char));
	printf("long: %d\n", sizeof(long));
	printf("double: %d\n", sizeof(double));

	return 0;
}
