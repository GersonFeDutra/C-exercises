#include <stdio.h>
#include <stdlib.h>
#include <locale.h>


/* Calcula o produto entre dois n�meros usando apenas soma, subtra��o e abs (m�dulo) */
int main() {
	setlocale(LC_ALL, "Portuguese");
	
	int a, b, aabs, babs, i, product = 0;
	
	printf("Digite dois n�meros inteiros:\na = ");
	scanf("%d", &a);
	aabs = abs(a);
	
	printf("b = ");
	scanf("%d", &b);
	babs = abs(b);
	
	if ((a < 0 && b > 0) || (a > 0 && b < 0))
		
		for (i = babs; i > 0; --i)
			product -= aabs;
	
	else
		for (i = 0; i < babs; ++i)
			product += aabs;
	
	printf("%d x %d = %d", a, b, product);
	
	return 0;
}

