#include <stdio.h>
#include <locale.h>


int main() {
	setlocale(LC_ALL, "Portuguese");
	
	float mass, height, imc;
	
	printf("Quanto voc� pesa? (kg) ");
	scanf("%f", &mass);
	
	printf("Qual a sua altura? (m) ");
	scanf("%f", &height);
	
	imc = mass / (height * height);
	
	if (imc <= 20) {
		printf("Voc� est� abaixo do peso.");
	}
	else if (imc <= 25) {
		printf("Voc� est� com peso normal.");
	}
	else if (imc <= 30) {
		printf("Voc� est� com sobrepeso.");
	}
	else if (imc <= 40) {
		printf("Voc� est� obeso.");
	}
	else {
		printf("Voc� est� com obesidade m�rbida.");
	}
	return 0;
}

