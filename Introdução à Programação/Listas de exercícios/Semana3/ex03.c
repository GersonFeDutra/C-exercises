#include <stdio.h>
#include <locale.h>


int main() {
	setlocale(LC_ALL, "Portuguese");
	
	int a, b;
	printf("Insira dois números inteiros:\n");
	
	printf("numerador = ");
	scanf("%d", &a);
	
	printf("denominador = ");
	scanf("%d", &b);
	
	if (b == 0) {
		printf("Não é possível dividir por 0.");
	}
	
	if (a % b == 0) {
		printf("%d é divisivel por %d.", a, b);
	}
	else {
		printf("%d não é divisivel por %d.", a, b);
	}
	
	return 0;
}

