#include <stdio.h>
#include <locale.h>


int main() {
	setlocale(LC_ALL, "Portuguese");
	
	float a, b, c;
	int ab, ac, bc;
	
	printf("Digite 3 n�meros: ");
	scanf("%f %f %f", &a, &b, &c);
	ab = a > b;
	ac = a > c;
	bc = b > c;
	
	if (a > b && a > c) {
		printf("%.3f � o maior n�mero.\n", a);
	}
	else if (b > a && b > c) {
		printf("%.3f � o maior n�mero.\n", b);
	}
	else {
		printf("%.3f � o maior n�mero.\n", c);
	}
	
	if (a < b && a < c) {
		printf("%.3f � o menor n�mero.", a);
	}
	else if (b < a && b < c) {
		printf("%.3f � o menor n�mero.", b);
	}
	else {
		printf("%.3f � o menor n�mero.", c);
	}
	
	return 0;
}

