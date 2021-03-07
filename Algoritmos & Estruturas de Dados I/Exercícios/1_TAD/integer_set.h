#define MAX_SIZE 10

// Definição do conjunto em 'integer_set.c'
/* Um Tipo Abstrato de Dados que armazena um conjunto de inteiros. */
typedef struct integer_set IntSet;

/* Cria um conjunto vazio. */
IntSet* new_set(void);

// `fill` e `fill_in` fazem basicamente o mesmo; a diferença é que `fill_in` é preenchido pelo
// usuário enquanto que `fill` é aplicado diretamente por código (auxiliando nos testes).
/* Dá entrada a um conjunto inicialmente vazio, sem permitir a repetição de elementos. */
void fill_in(IntSet *set);
/* Preenche um conjunto sobrescrevendo seus valores, sem repetição de elementos. A função retorna
1 (verdadeiro) ou 0 (falso) indicando se a operação ocorreu com sucesso. Se o vetor passado for
maior que MAX_SIZE, os valore excedentes serão ignorados. */
int fill(IntSet *set, int *arr, int size);

/* Faz a união entre dois conjutos, desde que não excedam o limite de 10 elementos; se for o caso a
função retornará 0 (falso booleano). Se a união ocorrer bem, retornará 1 (verdadeiro booleano). O
conjunto resultante da união será passado para `set_out`. Se houver falha `set_out` será um conjunto
vazio. */
int merge(IntSet *set_a, IntSet *set_b, IntSet *set_out);

/* Realiza a operação de intersecção entre dois conjuntos; retorna o conjunto resultante. */
IntSet* intersection(IntSet *set_a, IntSet *set_b);

/* Realiza a operação de diferença entre dois conjuntos: A - B; retorna o conjunto resultante. */
IntSet* diff(IntSet *set_a, IntSet *set_b);

/* Verifica se um conjunto A está contido em outro conjunto B; retorna 0 (falso) ou 1 (verdadeiro) */
int is_contained(IntSet *set_a, IntSet *set_b);

/* Envia o conjunto complementar de A (menor) em relação à B (maior) para `set_out`, apenas se A
está contido em B: retorno booleano. */
int complementary(IntSet *smaller_set, IntSet *bigger_set, IntSet *set_out);


/* Imprime os elementos do conjunto. */
void print_set(IntSet *set);
