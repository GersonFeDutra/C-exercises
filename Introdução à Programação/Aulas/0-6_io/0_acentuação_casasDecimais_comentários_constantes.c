#include <stdio.h>
#include <locale.h>
#define PI 3.1415 // Constante PI


int main() {
	/* Coment�rios:
	Coment�rio de m�ltiplas linhas.
	*/
	// Coment�rio de linha �nica.
	setlocale(LC_ALL, "Portuguese"); // Define a linguagem padr�o para o portugu�s, afetando entrada e sa�da de dados.
	const float PHI = 1.618;
	
	printf("O valor de PI �: %.4f\n", PI);
	printf("O valor de PHI �: %.4f\n", PHI);
	
	float a, b;
	printf("Digite o primeiro n�mero: ");
	scanf("%f", &a);
	printf("Digite o segundo n�mero: ");
	scanf("%f", &b);
	printf("\nA soma dos dois n�meros �: %3.2f\n", a + b);
	printf("\n");
	
	float celsius;
	printf("Digite a temperatura em Celsius: C�");
	scanf("%f", &celsius);
	printf("A temperatura digitada em Fahrenheit �: F�%5.3f", 9 * celsius / 5 + 32);
	return 0;
}

