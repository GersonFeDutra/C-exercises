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
		printf("Parab�ns, voc� foi aprovado!");
	}
	else {
		printf("Voc� far� prova final.");
	}
	
	return 0;
}

