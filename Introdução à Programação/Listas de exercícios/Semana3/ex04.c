#include <stdio.h>
#include <locale.h>


int main() {
	setlocale(LC_ALL, "Portuguese");
	
	float a, b, c, higher;
	printf("Insira 3 números quaisquer:\n");
	
	printf("a = ");
	scanf("%f", &a);
	higher = a;
	
	printf("b = ");
	scanf("%f", &b);
	
	printf("c = ");
	scanf("%f", &c);
	
	if (b > a && b > c) {
		higher = b;
	}
	else if (c > a && c > b) {
		higher = c;
	}
	
	printf("O maior número é o %.4f.", higher);
	
	return 0;
}

