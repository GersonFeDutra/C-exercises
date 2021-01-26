#include <stdio.h>
#include <locale.h>
/*
 _          _ _                         _     _ 
| |        | | |                       | |   | |
| |__   ___| | | _____      _____  _ __| | __| |
| '_ \ / _ \ | |/ _ \ \ /\ / / _ \| '__| |/ _` |
| | | |  __/ | | (_) \ V  V / (_) | |  | | (_| |
|_| |_|\___|_|_|\___/ \_/\_/ \___/|_|  |_|\__,_|
*/


int main() {
	setlocale(LC_ALL, "Portuguese");
	
	float x;
	printf("Digite um número qualquer: ");
	scanf("%f", &x);
	printf("O número digitado foi: %.2f", x);
	
	return 0;
}

