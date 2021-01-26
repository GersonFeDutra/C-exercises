#include <stdio.h>
#include <locale.h>


/* 8. Dada a série de Fibonacci formada pela sequência 1, 1, 2, 3, 5, 8, 13, 21, 34..., crie um algoritmo
que receba um número n do usuário e que calcule e imprima a soma dos n primeiros números da série. */
int main() {
	setlocale(LC_ALL, "Portuguese");
	
	int n, i, fibo = 0, last = 1, cache, sum = 0;
	printf("Quantos números da sequência Fibonachi você deseja somar? ");
	scanf("%d", &n);
	printf("0"); // Embora o 0 apareça na sequência ele não entra na quantidade de números da contagem, 
	// ex.: ao entrar 1 a saída será: "0 + 1"
	
	for (i = 1; i <= n; ++i) {
		cache = fibo;
		fibo += last;
		last = cache;
		sum += fibo;
		printf(" + %d", fibo);
	}
	
	printf(" = %d", sum);
	
	return 0;
}

