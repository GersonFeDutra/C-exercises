#include <stdio.h>
#include <locale.h>


int main() {
	setlocale(LC_ALL, "Portuguese");
	
	int a, b;
	printf("Insira dois n�meros inteiros:\n");
	
	printf("numerador = ");
	scanf("%d", &a);
	
	printf("denominador = ");
	scanf("%d", &b);
	
	if (b == 0) {
		printf("N�o � poss�vel dividir por 0.");
	}
	
	if (a % b == 0) {
		printf("%d � divisivel por %d.", a, b);
	}
	else {
		printf("%d n�o � divisivel por %d.", a, b);
	}
	
	return 0;
}

