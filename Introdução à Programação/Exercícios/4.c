#include <stdio.h>
#include <locale.h>


int main() {
	setlocale(LC_ALL, "Portuguese");
	void type_of_triangle(float, float, float);
	
	float a, b, c;
	printf("Indique 3 medidas para um triângulo 'ABC': ");
	scanf("%f %f %f", &a, &b, &c);
	
	if (!(c < a + b && a < b + c && b < c + a)) {
		printf("As medidas %.2f, %.2f e %.2f não formam um triângulo.", a, b, c);
	}
	else {
		printf("As medidas %.2f, %.2f e %.2f formam um triângulo.\n", a, b, c);
		type_of_triangle(a, b, c);
	}
	
	return 0;
}


void type_of_triangle(float a, float b, float c) {
	
	if (a == b || b == c) {
		
		if (a == c) {
			printf("O triângulo é equilátero.");
		}
		else {
			printf("O triângulo é isósceles.");
		}
	}
	else if (a == c) {
		printf("O triângulo é isósceles.");
	}
	else {
		printf("O triângulo é escaleno.");
	}
}

