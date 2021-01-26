#include <stdio.h>
#include <locale.h>


/* 4. Elaborar um programa que leia dois valores inteiros (a e b). Em seguida faça uma
função que retorne a soma do dobro dos dois numeros lidos. Além disso, a função deverá
armazenar o dobro de a na própria variável a e o dobro de b na própria variável b. */
double_and_getsum(int *a, int *b) {
	*a = 2 * *a;
	*b = 2 * *b;
	
	return *a + *b;
}


int main() {
	setlocale(LC_ALL, "Portuguese");
	
	int a, b, out;
	printf("Insira dois valores inteiros:\na = ");
	scanf("%d", &a);
	printf("b = ");
	scanf("%d", &b);
	
	out = double_and_getsum(&a, &b);
	printf("\na = %d\nb = %d\na + b = %d", a, b, out);
	
	return 0;
}

