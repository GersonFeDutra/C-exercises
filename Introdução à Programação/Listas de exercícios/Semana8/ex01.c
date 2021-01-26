#include <stdio.h>
#include <locale.h>


/* 1. Dada a sequência de fibonacci [1, 1, 2, 3, 5, 8, 13, 21, 34, 55...], faça uma função que
tenha como parâmetro um inteiro n e que retorna o número da sequência de Fibonacci
que está na posição n. */
int fibonacci(int n) {
	
	if (n < 1)
		return 0; // Flag de erro de entrada.
	
	int i, fibo = 0, last = 1, cache;
	
	for (i = 0; i < n; ++i) {
		cache = fibo;
		fibo += last;
		last = cache;
	}
	
	return fibo;
}

int main() {
	setlocale(LC_ALL, "Portuguese");
		
	int n;
	
	printf("Digite a posição do número na sequência fibonacci que deseja visualizar: ");
	scanf("%d", &n);
	
	if ((n = fibonacci(n)) > 0)
		printf("%d", n);
	else
		printf("A posição indicada é inválida.");
	
	return 0;
}

