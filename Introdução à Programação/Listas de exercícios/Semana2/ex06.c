#include <stdio.h>
#include <locale.h>


int main() {
	setlocale(LC_ALL, "Portuguese");
	
	int nule, white, valid, total;
	printf("Quantos votos nulos houveram nessa elei��o? ");
	scanf("%d", &nule);
	printf("Quantos votos brancos houveram nessa elei��o? ");
	scanf("%d", &white);
	printf("Quantos votos v�lidos houveram nessa elei��o? ");
	scanf("%d", &valid);
	total = nule + white + valid;
	printf("Nessa elei��o houve um total de %d votos.\n", total);
	printf(
			"%.1f%% foram nulos, %.1f%% foram brancos, e %.1f%% foram v�lidos.",
			1.0 * nule / total * 100.0, (float) white / total * 100.0, (float) valid / total * 100.0
	);
	
	return 0;
}

