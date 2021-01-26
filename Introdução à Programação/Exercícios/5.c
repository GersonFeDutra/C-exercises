#include <stdio.h>
#include <locale.h>


int main() {
	setlocale(LC_ALL, "Portuguese");
	int i, number;
	
	printf("Insira um número entre 1-9: ");
	scanf("%d", &number);
	
	for (i = 1; i <= 10; ++i)
		printf("%d x %d = %d\n", number, i, number * i);
	
	printf("Fim do programa.");
	
	return 0;
}

