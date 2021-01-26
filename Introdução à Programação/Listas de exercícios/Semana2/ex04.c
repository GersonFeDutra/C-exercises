#include <stdio.h>
#include <locale.h>

#define PI 3.1415


int main() {
	setlocale(LC_ALL, "Portuguese");
	
	float radius;
	printf("Digite o raio de um círculo qualquer: (cm) ");
	scanf("%f", &radius);
	printf("A área de um círculo com %.2fcm de raio é %.2fcm².", radius, PI * radius * radius);
	
	return 0;
}

