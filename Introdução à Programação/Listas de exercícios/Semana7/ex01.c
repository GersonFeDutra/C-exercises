#include <stdio.h>
#include <locale.h>


/* 1. Dada a sequência de bonacci {1, 1, 2, 3, 5, 8, 13, 21, 34, 55...} que pode ser calculada
através de: fib(x) = {1, se x = 1 ou x = 2;		fib(x - 1) + f ib(x - 2), caso contrário}
Faça uma função recursiva que receba um parâmetro inteiro x e retorne o número da sequência
na posição x. */
// Apenas entradas maiores que zero devem ser passadas.
// Como o valor já é filtrado antes da chamada da função, nesse caso, não houve necessidade de tratar valores menores ou iguais à zero.
int fibonacci(int x) {
	
	if (x == 2 || x == 1)
		return 1;
	
	return fibonacci(x - 1) + fibonacci(x - 2);;
}


int main() {
	setlocale(LC_ALL, "Portuguese");
	
	int i = 0;
	
	printf("Digite a posição do número na sequência fibonacci que deseja visualizar: ");
	
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

