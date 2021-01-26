#include <stdio.h>
#include <locale.h>


int main() {
	setlocale(LC_ALL, "Portuguese");
	
	int nule, white, valid, total;
	printf("Quantos votos nulos houveram nessa eleição? ");
	scanf("%d", &nule);
	printf("Quantos votos brancos houveram nessa eleição? ");
	scanf("%d", &white);
	printf("Quantos votos válidos houveram nessa eleição? ");
	scanf("%d", &valid);
	total = nule + white + valid;
	printf("Nessa eleição houve um total de %d votos.\n", total);
	printf(
			"%.1f%% foram nulos, %.1f%% foram brancos, e %.1f%% foram válidos.",
			1.0 * nule / total * 100.0, (float) white / total * 100.0, (float) valid / total * 100.0
	);
	
	return 0;
}

