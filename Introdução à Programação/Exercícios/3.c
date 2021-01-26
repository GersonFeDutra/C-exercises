#include <stdio.h>
#include <locale.h>


int main() {
	setlocale(LC_ALL, "Portuguese");
	
	float a, b, c;
	int ab, ac, bc;
	
	printf("Digite 3 números: ");
	scanf("%f %f %f", &a, &b, &c);
	ab = a > b;
	ac = a > c;
	bc = b > c;
	
	if (a > b && a > c) {
		printf("%.3f é o maior número.\n", a);
	}
	else if (b > a && b > c) {
		printf("%.3f é o maior número.\n", b);
	}
	else {
		printf("%.3f é o maior número.\n", c);
	}
	
	if (a < b && a < c) {
		printf("%.3f é o menor número.", a);
	}
	else if (b < a && b < c) {
		printf("%.3f é o menor número.", b);
	}
	else {
		printf("%.3f é o menor número.", c);
	}
	
	return 0;
}

