#include <stdio.h>
#include <locale.h>


/* Fa�a um programa que receba v�rios n�meros. O programa deve ser finalizado
quando o n�mero 0 for digitado. Antes de finalizar o programa, deve-se exibir
na tela a m�dia das notas digitadas. */
int main() {
	setlocale(LC_ALL, "Portuguese");
	
	float n = 1, soma = 0, c = 0;
	
	while (1) {
		printf("Digite um n�mero: (0 para sair) ");
		scanf("%f", &n);
		
		if (n == 0)
			break;
		
		soma += n;
		++c;
	}
	
	printf("A m�dia entre esses n�meros �: %.2f", soma / (c > 0 ? c : 1));
	
	return 0;
}

