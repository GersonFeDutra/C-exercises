#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100

struct tnode { /* the tree node */
    char *word;               /* points to the text */
    int count;                /* #of occurrences */
    struct tnode *left;       /* left node */
    struct tnode *right;      /* right node */
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

/** Write a program that prints the distinct words in its input
 * sorted into decreasing order of frequency of occurrence.
 * Precede each word by its count.
 * 
 * @note Usage: [-x] remove noise words.
 **/
int main(int argc, char const *argv[])
{
    #define bool int
    #define true 1
    #define false 0

    struct tnode *root;
	char word[MAXWORD];
    size_t ln, cn;

    bool remove_noise = false;
    if (argc != 1)
        remove_noise = *argv[1] == '-' && *(argv[1] + 1) == 'x';

    root = NULL;
    if (remove_noise) {
        while (getword(word, MAXWORD, &ln, &cn) != EOF)
            if (isalpha(word[0]) && binsearch(word, noise_words, NKEYS) == NOMATCH)
                root = addtree(root, word, ln, cn);
    }
    else {
        while (getword(word, MAXWORD, &ln, &cn) != EOF)
            if (isalpha(word[0]))
                root = addtree(root, word, ln, cn);
    }
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
    }
    else if ((cond = strcmp(w, p->word)) == 0) /* repeated word */
        p->count++;
    else if (cond < 0)
        p->left = addtree(p->left, w, ln, cn);
    else
        p->right = addtree(p->right, w, ln, cn);

    return p;
}

/* tree_print: post-order print of the tree p */
void tree_print(struct tnode *p)
{
    if (p != NULL) {
        tree_print(p->right);
        printf("%4d %s\n", p->count, p->word);
        tree_print(p->left);
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
