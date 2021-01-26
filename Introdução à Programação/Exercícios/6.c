#include <stdio.h>
#include <locale.h>


/* Faça um programa que receba vários números. O programa deve ser finalizado
quando o número 0 for digitado. Antes de finalizar o programa, deve-se exibir
na tela a média das notas digitadas. */
int main() {
	setlocale(LC_ALL, "Portuguese");
	
	float n = 1, soma = 0, c = 0;
	
	while (1) {
		printf("Digite um número: (0 para sair) ");
		scanf("%f", &n);
		
		if (n == 0)
			break;
		
		soma += n;
		++c;
	}
	
	printf("A média entre esses números é: %.2f", soma / (c > 0 ? c : 1));
	
	return 0;
}

