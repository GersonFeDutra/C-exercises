#include <stdio.h>
#include <locale.h>

#define PI 3.1415


int main() {
	setlocale(LC_ALL, "Portuguese");
	
	float radius;
	printf("Digite o raio de um c�rculo qualquer: (cm) ");
	scanf("%f", &radius);
	printf("A �rea de um c�rculo com %.2fcm de raio � %.2fcm�.", radius, PI * radius * radius);
	
	return 0;
}

