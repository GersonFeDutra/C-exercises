#include <stdio.h>
#include <locale.h>


/* 4. Fa�a uma fun��o que recebe um valor em metros (como par�metro) e retorna um valor
em cent�metros. */
float m2cm(float meters) {
	return meters * 100.0;
}

int main() {
	setlocale(LC_ALL, "Portuguese");
	
	float m;
	printf("Insira um valor em metros: (m) ");
	scanf("%f", &m);
	
	printf("%.2fm = %.0fcm.", m, m2cm(m));
	
	return 0;
}

