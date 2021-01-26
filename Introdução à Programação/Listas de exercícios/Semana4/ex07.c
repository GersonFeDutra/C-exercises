#include <stdio.h>
#include <locale.h>


/* 7. Fa�a um algoritmo que recebe dez n�meros digitados pelo usu�rio. Ap�s isso, o algoritmo
deve informar o maior e o menor n�mero digitado (Utilize estruturas de repeti��o). */
int main() {
	setlocale(LC_ALL, "Portuguese");
	
	int i = 2;
	float n, higher, lower;
	
	printf("Insira 10 n�meros:\n1� = ");
	scanf("%f", &higher);
	lower = higher;
	
	/* `for` podeira ser usado nesse caso, mas seguindo a recomenda��o do professor
	(no chat privado do classroom), o exerc�o fora resolvido com `while`. */
	while (i <= 10) {
		printf("%d� = ", i);
		scanf("%f", &n);
		
		if (n > higher)
			higher = n;
		
		else if (n < lower)
			lower = n;
		
		++i;
	}
	
	printf("O maior n�mero � %.1f\n", higher);
	printf("O menor n�mero � %.1f", lower);
	
	return 0;
}

