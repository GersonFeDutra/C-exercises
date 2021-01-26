#include <stdio.h>
#include <locale.h>
#define PI 3.1415 // Constante PI


int main() {
	/* Comentários:
	Comentário de múltiplas linhas.
	*/
	// Comentário de linha única.
	setlocale(LC_ALL, "Portuguese"); // Define a linguagem padrão para o português, afetando entrada e saída de dados.
	const float PHI = 1.618;
	
	printf("O valor de PI é: %.4f\n", PI);
	printf("O valor de PHI é: %.4f\n", PHI);
	
	float a, b;
	printf("Digite o primeiro número: ");
	scanf("%f", &a);
	printf("Digite o segundo número: ");
	scanf("%f", &b);
	printf("\nA soma dos dois números é: %3.2f\n", a + b);
	printf("\n");
	
	float celsius;
	printf("Digite a temperatura em Celsius: C°");
	scanf("%f", &celsius);
	printf("A temperatura digitada em Fahrenheit é: F°%5.3f", 9 * celsius / 5 + 32);
	return 0;
}

