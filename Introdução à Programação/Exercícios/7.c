#include <stdio.h>
#include <locale.h>


int main() {
	setlocale(LC_ALL, "Portuguese");
	
	int n;
	do {
		printf("1 - continuar\n2 - sair\n");
		scanf("%d", &n);
	}
	while (n != 2);
	
	return 0;
}

