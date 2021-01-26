#include <stdio.h>
#include <locale.h>


/* 7. Fa�a uma fun��o que recebe, por par�metro, um valor inteiro e positivo e retorna o
n�mero de divisores desse valor. */
int ndivisors(int n) {
	
	if (n <= 0) return 0;
	if (n == 1)	return 1;
	
	int i, amount = 2; // Todos os valores maiores que 1, possuem pelo menos 2 divisores, i.e: 1 e ele mesmo.
	
	for (i = 2; i <= n / 2; ++i) {
		if (n % i == 0)
			++amount;
	}
	
	return amount;
}

int main() {
	setlocale(LC_ALL, "Portuguese");
	
	int n;
	
	while (1) {
		printf("Insira um valor inteiro positivo: ");
		scanf("%d", &n);
		
		if (n >= 0) {
			break;
		}
	}
	
	printf("%d possui %d divisor(es).", n, ndivisors(n));
	
	return 0;
}

