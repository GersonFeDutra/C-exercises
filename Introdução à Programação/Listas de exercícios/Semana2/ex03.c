#include <stdio.h>
#include <locale.h>


int main() {
	setlocale(LC_ALL, "Portuguese");
	
	float distance;
	printf("Digite uma dist�ncia em metros (m): ");
	scanf("%f", &distance);
	printf("%.2fm equivale � %.0fcm", distance, distance * 100);
	
	return 0;
}

