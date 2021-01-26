#include <stdio.h>
#include <locale.h>


int main() {
	setlocale(LC_ALL, "Portuguese");

	int a = 1;
	float b = 2.0;
	char c = '3';
	
	int *aa = &a;
	float *bb = &b;
	char *cc = &c;
	
	printf("a = %d, b = %f, c = %c\n", a, b, c);
	
	//a++; // Note a diferença
	//*aa++;
	++*aa;
	*bb += 1;
	*cc = '5';
	printf("a = %d, b = %f, c = %c\n", a, b, c);

	return 0;
}
