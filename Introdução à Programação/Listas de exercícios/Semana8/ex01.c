#include <stdio.h>
#include <locale.h>


/* 1. Dada a sequ�ncia de fibonacci [1, 1, 2, 3, 5, 8, 13, 21, 34, 55...], fa�a uma fun��o que
tenha como par�metro um inteiro n e que retorna o n�mero da sequ�ncia de Fibonacci
que est� na posi��o n. */
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
	
	printf("Digite a posi��o do n�mero na sequ�ncia fibonacci que deseja visualizar: ");
	scanf("%d", &n);
	
	if ((n = fibonacci(n)) > 0)
		printf("%d", n);
	else
		printf("A posi��o indicada � inv�lida.");
	
	return 0;
}

