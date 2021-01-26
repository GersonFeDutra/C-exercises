#include <stdio.h>
#include <locale.h>


int main() {
	void higher_integer(void), car_age(void), vehicle_speed(void), pupil_medium(void), increase_salary(void);
	setlocale(LC_ALL, "Portuguese");
	
	higher_integer();
	printf("\n");
	car_age();
	printf("\n");
	vehicle_speed();
	printf("\n");
	pupil_medium();
	printf("\n");
	increase_salary();
	
	return 0;
}


void higher_integer() {
	int a, b;
	printf("Digite dois valores inteiros: ");
	scanf("%d %d", &a, &b);
	
	if (a > b) {
		printf("O primeiro n�mero � maior.\n");
	}
	else if (a < b) {
		printf("O segundo n�mero � maior.\n");
	}
	else {
		printf("Os n�meros digitados s�o iguais.\n");
	}
}


void car_age() {
	int age;
	
	printf("Digite a idade de seu carro: ");
	scanf("%d", &age);
	
	if (age <= 3) {
		printf("Seu carro � novo.\n");
	}
	else {
		printf("Seu carro � velho.\n");
	}
}


void vehicle_speed() {
	const float MAX_SPEED = 80.0;
	float speed;
	
	printf("Qual a velocidade do ve�culo? (km/h) ");
	scanf("%f", &speed);
	
	if (speed > MAX_SPEED) {
		printf("O motorista do ve�culo ser� multado em R$ %.2f.\n", 5 * (speed - MAX_SPEED));
	}
	
	printf("Dirija com cuidado!\n");
}


void pupil_medium() {
	float weighted_medium, evaluation, final_medium;
	
	printf("Digite a m�dia ponderada: ");
	scanf("%f", &weighted_medium);
	printf("Digite a nota da avalia��o final: ");
	scanf("%f", &evaluation);
	final_medium = (weighted_medium + evaluation) / 2;
	
	if (final_medium >= 5) {
		printf("Aprovado!\n");
	}
	else {
		printf("Reprovado!\n");
	}
}


void increase_salary() {
	float salary, increase;
	printf("Qual o sal�rio do funcion�rio? R$ ");
	scanf("%f", &salary);
	
	if (salary > 1250) {
		increase = salary * 0.1;
	}
	else {
		increase = salary * 0.15;
	}
	printf("O funcion�rio receber� um almento de R$ %.2f, seu novo sal�rio � de R$ %.2f.", increase, salary + increase);
}

