#include <stdio.h>
#include <locale.h>


/* 8. Dada a s�rie de Fibonacci formada pela sequ�ncia 1, 1, 2, 3, 5, 8, 13, 21, 34..., crie um algoritmo
que receba um n�mero n do usu�rio e que calcule e imprima a soma dos n primeiros n�meros da s�rie. */
int main() {
	setlocale(LC_ALL, "Portuguese");
	
	int n, i, fibo = 0, last = 1, cache, sum = 0;
	printf("Quantos n�meros da sequ�ncia Fibonachi voc� deseja somar? ");
	scanf("%d", &n);
	printf("0"); // Embora o 0 apare�a na sequ�ncia ele n�o entra na quantidade de n�meros da contagem, 
	// ex.: ao entrar 1 a sa�da ser�: "0 + 1"
	
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

