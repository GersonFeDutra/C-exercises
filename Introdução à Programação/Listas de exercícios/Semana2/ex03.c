#include <stdio.h>
#include <locale.h>


int main() {
	setlocale(LC_ALL, "Portuguese");
	
	float distance;
	printf("Digite uma distância em metros (m): ");
	scanf("%f", &distance);
	printf("%.2fm equivale à %.0fcm", distance, distance * 100);
	
	return 0;
}

