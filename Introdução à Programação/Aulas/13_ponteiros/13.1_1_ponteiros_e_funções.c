#include <stdio.h>
#include <locale.h>


void shift(int *a, int *b) {
	int cache = *a;
	*a = *b;
	*b = cache;
}

int main() {
	setlocale(LC_ALL, "Portuguese");

	int a = 10, b = 20;
	printf("%d %d\n", a, b);
	
	shift(&a, &b);
	printf("%d %d\n", a, b);

	return 0;
}
