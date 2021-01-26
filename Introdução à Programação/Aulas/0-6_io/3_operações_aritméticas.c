#include <stdio.h>


int main() {
	printf("Soma: %d.\n", 1 + 2 + 3);
	printf("Subtracao: %d.\n", 5 - 3);
	printf("Multiplicacao: %f.\n", 5 * 7.5);
	printf("Divisao: %d.\n", 10 / 2);
	printf("Resto: %d.\n", 10 % 2);
	printf("\n");
	printf("Divisao com inteiros: %d.\n", 23 / 10);
	printf("Divisao: %f.\n", 7.0 / 2);
	printf("\nOrdem de precedencia:\n");
	printf("%d\n", 2 + 6 / 3);
	printf("%d\n", 2 + 3 * 5 + 4);
	printf("%d\n", 4 / 2 + 3 * 2 + 1);
	printf("\n");
	printf("%d\n", (3 + 6) / 3);
	printf("%d\n", (2 + 3) * (5 + 4));
	printf("%d", 16 / (4 - 3) * (2 + 2));
	return 0;
}

