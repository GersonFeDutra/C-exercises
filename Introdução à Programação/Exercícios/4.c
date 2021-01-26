#include <stdio.h>
#include <locale.h>


int main() {
	setlocale(LC_ALL, "Portuguese");
	void type_of_triangle(float, float, float);
	
	float a, b, c;
	printf("Indique 3 medidas para um tri�ngulo 'ABC': ");
	scanf("%f %f %f", &a, &b, &c);
	
	if (!(c < a + b && a < b + c && b < c + a)) {
		printf("As medidas %.2f, %.2f e %.2f n�o formam um tri�ngulo.", a, b, c);
	}
	else {
		printf("As medidas %.2f, %.2f e %.2f formam um tri�ngulo.\n", a, b, c);
		type_of_triangle(a, b, c);
	}
	
	return 0;
}


void type_of_triangle(float a, float b, float c) {
	
	if (a == b || b == c) {
		
		if (a == c) {
			printf("O tri�ngulo � equil�tero.");
		}
		else {
			printf("O tri�ngulo � is�sceles.");
		}
	}
	else if (a == c) {
		printf("O tri�ngulo � is�sceles.");
	}
	else {
		printf("O tri�ngulo � escaleno.");
	}
}

