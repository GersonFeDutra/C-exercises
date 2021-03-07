typedef struct matriz Matriz;

/* Cria uma matriz com as dimensões indicadas. */
Matriz *cria(int linhas, int colunas);

/* Libera a matriz da memória. */
void libera(Matriz *);

/* Retorna um valor da matriz nas coordenadas indicadas. */
float acessa(Matriz *, int linha, int coluna);

/* Atribui um valor à matriz nas coordenadas indicadas. */
void atribui(Matriz *, int linha, int coluna, float valor);

/* Retorna a quantidade de linhas da matriz. */
int linhas(Matriz *);

/* Retorna a quantidade de colunas da matriz. */
int colunas(Matriz *);
