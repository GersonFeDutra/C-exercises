#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100

struct element {
    size_t ln;               /* line number on which the element occurs */
    size_t cn;               /* line column on which the element occurs */
    struct element *next; /* the next element of the list */
}; /* an element from a list of line numbers */

struct tnode { /* the tree node */
    char *word;               /* points to the text */
    int count;                /* #of occurrences */
    struct tnode *left;       /* left node */
    struct tnode *right;      /* right node */
    struct element *lns_list; /* list of coordinates on which the word occurs */
    struct element *list_end; /* last element of lns_list, to ease insertion */
};

const char *noise_words[] = {
	"a",    "an",   "and",  "as",   "at",   "by",   "do",   "for",  "if",   "in",
    "it",   "not",  "nt",   "of",   "on",   "or",   "so",   "that", "the",  "then",
    "this", "those", "will",
}; // List of words that will be ignored by the program
#define NKEYS sizeof(noise_words) / sizeof(char *)
#define NOMATCH -1


struct tnode *addtree(struct tnode *, char *, size_t, size_t);
int binsearch(const char *, const char *[], int);
int getword(char *word, int lim, size_t *ln, size_t *cn);
void tree_print(struct tnode *);

/* cross-referencer
 * write a program that print a list of all words in a document, and, for each
 * word, a list of the line numbers on which it occurs. Remove noise words like
 * "the", "and", and so on.
 */
int main(void)
{
    struct tnode *root;
	char word[MAXWORD];
    size_t ln, cn;

    root = NULL;
    while (getword(word, MAXWORD, &ln, &cn) != EOF)
        if (isalpha(word[0]) && binsearch(word, noise_words, NKEYS) == NOMATCH)
            root = addtree(root, word, ln, cn);
    tree_print(root);

    return EXIT_SUCCESS;
}


/* binsearch: find word in tab[0]...tab[n-1] */
int binsearch(const char *word, const char *tab[], int n)
{
	int cond;
	int low, high, mid;

	low = 0;
	high = n - 1;
	while (low <= high) {
		mid = (low + high) / 2;

		if ((cond = strcmp(word, tab[mid])) < 0)
			high = mid - 1;
		else if (cond > 0)
			low = mid + 1;
		else
			return mid;
	}

	return NOMATCH; /* no match */
}


int acc_getch(size_t *ln, size_t *cn);
int getch(void);
void ungetch(int c);

/* getword: get next word of character from input
 * returns the coords of the word (Ln and Col) on which it appears */
int getword(char *word, int lim, size_t *ln, size_t *cn)
{
    int c;
    char *w = word;

    while (isspace(c = acc_getch(ln, cn)));
        /* ignore blanks */

    if (c != EOF)
        *w++ = c;

    if (!isalpha(c)) {
        *w = '\0';

        return c;
    }

    for ( ; --lim; w++)
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }

    *w = '\0';

    return word[0];
}


/* getch a character accounting the coordinates */
int acc_getch(size_t *ln, size_t *cn)
{
    int c = getch();

	if (c == '\n')
		++*ln, *cn = 0; /* account to next line */
	else
        ++*cn;          /* account to next character */

    return c;
}


#define TRUE 1
#define FALSE 0

static char buf; /* buffer for ungetch */
static unsigned short buffed = FALSE; /* next free position in buf */


int getch(void) /* get a (possibly pushed back) character */
{
    if (buffed) {
        buffed = FALSE;
        return buf;
    }
    return getchar();
}


void ungetch(int c) /* push character back on input */
{
    buffed = TRUE;
    buf = c;
}


/* alloc a new element on heap */
#define el_alloc() ((struct element *)malloc(sizeof(struct element)));

/* addtree: add a node with a w, with coordinates ln:cn, at or below t */
struct tnode *addtree(struct tnode *p, char *w, size_t ln, size_t cn)
{
    struct tnode *talloc(void);
    char *strdup(const char *);
    int cond;

    // TODO -> Error Checking for strdup and talloc
    if (p == NULL) { /* a new word has arrived */
        p = talloc(); /* make a new node */
        p->word = strdup(w);
        p->count = 1;
        p->left = p->right = NULL;

        /* add a new element to the coords list */
        p->list_end = p->lns_list = el_alloc();
        p->lns_list->ln = ln;
        p->lns_list->cn = cn;
        p->lns_list->next = NULL;
    }
    else if ((cond = strcmp(w, p->word)) == 0) { /* repeated word */
        p->list_end = p->list_end->next = el_alloc();
        p->list_end->next = NULL;
        p->list_end->ln = ln;
        p->list_end->cn = cn;
        p->count++;
    }
    else if (cond < 0)
        p->left = addtree(p->left, w, ln, cn);
    else
        p->right = addtree(p->right, w, ln, cn);

    return p;
}


/* prints a list of coordinates (Ln: line number, Col: column number) */
void list_print(struct element *el)
{
    if (el == NULL)
        return;

    printf("(Ln:%d, Col:%d)", el->ln, el->cn);

	for (el = el->next; el != NULL; el = el->next)
		printf(", (Ln:%d, Col:%d)", el->ln, el->cn);

	printf(".\n");
}


/* tree_print: in-order print of the tree p */
void tree_print(struct tnode *p)
{
    if (p != NULL) {
        tree_print(p->left);
        printf("%4d %s\f", p->count, p->word);
        list_print(p->lns_list);
        tree_print(p->right);
    }
}


/* talloc: make a tree node */
struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}


char *strdup(const char *s) /* strdup: make a duplicate of s */
{
    char *p;
    p = (char *) malloc(strlen(s) + 1); /* +1 for the '\0' */

    if (p != NULL)
        strcpy(p, s);

    return p;
}
