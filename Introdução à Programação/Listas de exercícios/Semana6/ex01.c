#include <stdio.h>
#include <locale.h>

/*
         _,----.
      ,-'     __`.
     /    .  /--\`)
    /  .  )\/_,--\
   /  ,'\/,-'    _\_
  |  /  ,' ,---'  __\
 ,' / ,:     _,-\'_,(
  (/ /  \ \,'   |'  _)         ,. ,.,.
   \/   |          '  \        \ ,. \ )
    \, ,-              \       /,' )//
     ; \'`      _____,-'      _|`  ,'
      \ `"\    (_,'_)     _,-'    ,'
       \   \       \  _,-'       ,'
       |, , )       `'       _,-'
       /`/ Y    ,    \   _,-'
          :    /      \-'
          |     `--.__\___
          |._           __)
          |  `--.___    _)
          |         `----'
         /                \
        '                . )
*//* 1. Faça um programa que preencha uma matriz de tamanho L × C (o tamanho deve ser
informado pelo usuário) e crie uma nova matriz sendo ela uma matriz transposta da
matriz L × C. */
int main() {
	setlocale(LC_ALL, "Portuguese");
	
	int l, c, i, j;
	int counter = 0;
	
	printf("Determine o tamanho da matriz:\nLinhas = ");
	scanf("%d", &l);
	printf("Colunas = ");
	scanf("%d", &c);
	
	int matrix[l][c];
	int transposed[c][l];
	
	printf("\nMatriz:\n");
	
	for (i = 0; i < l; ++i) {
		printf("|");
		
		for (j = 0; j < c; ++j) {
			matrix[i][j] = counter;
			printf(" %3d", matrix[i][j]);
			++counter;
		}
		printf(" |\n");
	}
	
	printf("\nMatriz Transposta:\n");
	
	for (j = 0; j < c; ++j) {
		printf("|");
		
		for (i = 0; i < l; ++ i) {
			transposed[j][i] = matrix[i][j];
			printf(" %3d", transposed[j][i]);
		}
		printf(" |\n");
	}
	
	return 0;
}

