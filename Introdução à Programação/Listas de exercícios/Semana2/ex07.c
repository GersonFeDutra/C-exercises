#include <stdio.h>
#include <locale.h>


int main() {
	setlocale(LC_ALL, "Portuguese");
	
	float kilometers;
	int days;
	printf("Quantos kil�metros o carro alugado percorreu? (km) ");
	scanf("%f", &kilometers);
	printf("Por quantos dias o carro foi alugado? ");
	scanf("%d", &days);
	printf("O pre�o do aluguel � de R$ %.2f.", days * 60.0 + kilometers * 0.15);
	
	return 0;
}

