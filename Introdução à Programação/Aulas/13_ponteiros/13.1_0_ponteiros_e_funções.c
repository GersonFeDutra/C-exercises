#include <stdio.h>
#include <locale.h>


void incremento_ref(int *x) {
	++*x;
}

void incremento_val(int x) {
	x++;
}

int main() {
	setlocale(LC_ALL, "Portuguese");

	int a = 10;
	int *pa = &a;
	
	incremento_val(a);
	printf("%d\n", a);
	
	incremento_ref(pa);
	printf("%d\n", a);

	return 0;
}
