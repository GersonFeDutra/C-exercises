#include <stdio.h>
#include <locale.h>


int main() {
	setlocale(LC_ALL, "Portuguese");
	
	int number;
	printf("Digite um número inteiro entre 1-9: ");
	scanf("%d", &number);
	
	switch (number) {
		case 1: printf("Lave as mãos."); break;
		case 2: printf("Passe álcool em gel."); break;
		case 3: printf("Use máscara."); break;
		case 4: printf("Cuide dos idosos."); break;
		case 5: printf("Cultive paciência."); break;
		case 6: printf("Cultive sabedoria."); break;
		case 7: printf("Ame o próximo."); break;
		case 8: printf("Exercite a disciplina."); break;
		case 9: printf("Acalme a mente."); break;
		default: printf("Código inválido.");
	}
	
	return 0;
}

