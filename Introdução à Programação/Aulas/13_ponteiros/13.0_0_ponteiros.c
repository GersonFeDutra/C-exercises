#include <stdio.h>
#include <locale.h>


int main() {
	setlocale(LC_ALL, "Portuguese");

	int a = 5;
	int *ponteiro = &a;
	
	printf("%d\n", ponteiro);
	printf("%d\n", *ponteiro);
	
	*ponteiro += 3;
	printf("%d\n", a);
	printf("%d\n", *ponteiro);
	
	*ponteiro = 15;
	printf("%d\n", a);
	
	a -= 1;
	printf("%d\n", *ponteiro);

	return 0;
}
