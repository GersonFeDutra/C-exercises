#include <stdio.h>
#include <locale.h>


int main() {
	setlocale(LC_ALL, "Portuguese");

	int inteiro = 25;
	char caractere = 'a';
	void *p;
	
	p = &inteiro;
	printf("Apontando para int: %d\n", *(int*)p);
	
	p = &caractere;
	printf("Apontando para char: %c\n", *(char*)p);
	
	char *pc = (char*)p;
	printf("Apontando para char: %c\n", *pc);

	return 0;
}
