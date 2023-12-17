#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100

struct tnode { /* the tree node */
    char *word;          /* points to the text */
    int count;           /* #of occurrences */
    struct tnode *left;  /* left node */
    struct tnode *right; /* right node */
};

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);

/* word frequency count */
int main()
{
    struct tnode *root;
    char word[MAXWORD];

    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            root = addtree(root, word);
    treeprint(root);

    return EXIT_SUCCESS;
}


int getch(void);
void ungetch(int c);


/* getword: get next word of character from input */
int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()));
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


struct tnode *talloc(void);
char *strdup(const char *);

/* addtree: add a node with a w, at or below t */
struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;

    // TODO -> Error Checking for strdup and talloc
    if (p == NULL) { /* a new word has arrived */
        p = talloc(); /* make a new node */
        p->word = strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    }
    else if ((cond = strcmp(w, p->word)) == 0)
        p->count++; /* repeated word */
    else if (cond < 0) /* "less than" into left subtree */
        p->left = addtree(p->left, w);
    else
        p->right = addtree(p->right, w);

    return p;
}


/* treeprint: in-order print of the tree p */
void treeprint(struct tnode *p)
{
    if (p != NULL) {
        treeprint(p->left);
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right);
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
