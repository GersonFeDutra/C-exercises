#include <stdio.h>
#include <locale.h>


/* 5. Fa�a uma fun��o que recebe um valor em Celsius (como par�metro) e retorna um valor
em Farenheit. */
float celsius2fahr(float celsius) {
	return celsius * (9.0 / 5.0) + 32.0;
}

int main() {
	setlocale(LC_ALL, "Portuguese");
	
	float c;
	printf("Insira um valor em Celsius: �C ");
	scanf("%f", &c);
	
	printf("%.1f�C = %.1f�F.", c, celsius2fahr(c));
	
	return 0;
}

