#include <stdio.h>
#include <locale.h>


/* 7. Faça um algoritmo que recebe dez números digitados pelo usuário. Após isso, o algoritmo
deve informar o maior e o menor número digitado (Utilize estruturas de repetição). */
int main() {
	setlocale(LC_ALL, "Portuguese");
	
	int i = 2;
	float n, higher, lower;
	
	printf("Insira 10 números:\n1° = ");
	scanf("%f", &higher);
	lower = higher;
	
	/* `for` podeira ser usado nesse caso, mas seguindo a recomendação do professor
	(no chat privado do classroom), o exercío fora resolvido com `while`. */
	while (i <= 10) {
		printf("%d° = ", i);
		scanf("%f", &n);
		
		if (n > higher)
			higher = n;
		
		else if (n < lower)
			lower = n;
		
		++i;
	}
	
	printf("O maior número é %.1f\n", higher);
	printf("O menor número é %.1f", lower);
	
	return 0;
}

