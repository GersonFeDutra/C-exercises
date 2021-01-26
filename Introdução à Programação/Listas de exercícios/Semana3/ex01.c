#include <stdio.h>
#include <locale.h>


int main() {
	setlocale(LC_ALL, "Portuguese");
	
	float a, b, c, medium;
	printf("Insira 3 notas:\n");
	
	printf("a = ");
	scanf("%f", &a);

	printf("b = ");
	scanf("%f", &b);
	
	printf("c = ");
	scanf("%f", &c);
	
	medium = (a + b + c) / 3;
	
	if (medium >= 7) {
		printf("Parabéns, você foi aprovado!");
	}
	else {
		printf("Você fará prova final.");
	}
	
	return 0;
}

