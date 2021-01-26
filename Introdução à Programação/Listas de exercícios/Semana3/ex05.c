#include <stdio.h>
#include <locale.h>


int main() {
	setlocale(LC_ALL, "Portuguese");
	
	float mass, height, imc;
	
	printf("Quanto você pesa? (kg) ");
	scanf("%f", &mass);
	
	printf("Qual a sua altura? (m) ");
	scanf("%f", &height);
	
	imc = mass / (height * height);
	
	if (imc <= 20) {
		printf("Você está abaixo do peso.");
	}
	else if (imc <= 25) {
		printf("Você está com peso normal.");
	}
	else if (imc <= 30) {
		printf("Você está com sobrepeso.");
	}
	else if (imc <= 40) {
		printf("Você está obeso.");
	}
	else {
		printf("Você está com obesidade mórbida.");
	}
	return 0;
}

