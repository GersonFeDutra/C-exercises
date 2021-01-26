#include <stdio.h>
#include <locale.h>


/* 1. Dada a sequ�ncia de bonacci {1, 1, 2, 3, 5, 8, 13, 21, 34, 55...} que pode ser calculada
atrav�s de: fib(x) = {1, se x = 1 ou x = 2;		fib(x - 1) + f ib(x - 2), caso contr�rio}
Fa�a uma fun��o recursiva que receba um par�metro inteiro x e retorne o n�mero da sequ�ncia
na posi��o x. */
// Apenas entradas maiores que zero devem ser passadas.
// Como o valor j� � filtrado antes da chamada da fun��o, nesse caso, n�o houve necessidade de tratar valores menores ou iguais � zero.
int fibonacci(int x) {
	
	if (x == 2 || x == 1)
		return 1;
	
	return fibonacci(x - 1) + fibonacci(x - 2);;
}


int main() {
	setlocale(LC_ALL, "Portuguese");
	
	int i = 0;
	
	printf("Digite a posi��o do n�mero na sequ�ncia fibonacci que deseja visualizar: ");
	
	while (1) {
		scanf("%d", &i);
		
		if (i > 0)
			break;
		else
			printf("A entrada deve ser maior que zero, por favor tente novamente: ");
	}
	
	printf("%d", fibonacci(i));
	
	return 0;
}

