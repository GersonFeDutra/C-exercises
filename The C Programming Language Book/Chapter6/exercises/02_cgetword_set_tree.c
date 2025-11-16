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

struct set_tnode { /* the tree node of a set of matching words */
    struct tnode *tree;      /* set: a btree of words */
    int size;                /* #of elements on set */
    struct set_tnode *left;  /* left node */
    struct set_tnode *right; /* right node */
};

// keywords of C that will be ignored in the counting (tokens are not variables names)
const char *keytab[] = {
	"#define",  "#else",    "#if",      "#ifdef",   "#include", "#pragma",  "#undef",
    "auto",     "break",    "case",     "char",     "const",    "continue", "default",
    "do",       "double",   "else",     "enum",     "extern",   "float",    "for",
    "goto",     "if",       "int",      "long",     "register", "return",   "short",
    "signed",   "sizeof",   "static",   "struct",   "switch",   "typedef",  "union",
    "unsigned", "void",     "volatile", "while",
}; // The keywords are stored in increasing order so we can use a binary search to search then.
#define NKEYS sizeof(keytab) / sizeof(char *)
#define NOMATCH -1


int getword(char *, int);

/** variable frequency count
 * Write a program that reads a C program and prints in alphabetical order each
 * group of variables names that are identical in the first 6 characters, but
 * different somewhere thereafter.
 * Don't count words within strings and comments.
 * Make 6 a parameter that can be set from command line.
 **/
int main(int argc, char const *argv[])
{
	struct set_tnode *root, *addset(struct set_tnode *, char *, int);
    int binsearch(const char *, const char *[], int);
    void set_tree_print(struct set_tnode *, int);

	char word[MAXWORD];
    int n = 6;
    root = NULL;

    if (argc > 1)
        n = atoi(argv[1]);

    while (getword(word, MAXWORD) != EOF)
        if (( isalpha(word[0]) && binsearch(word, keytab, NKEYS) == NOMATCH )
              || word[0] == '_')
            root = addset(root, word, n);
    set_tree_print(root, n);

    return EXIT_SUCCESS;
}


struct tnode *addtree(struct tnode *, char *);
void tree_print(struct tnode *);

struct set_tnode *set_talloc(void);
unsigned match(char *a, char *b, int n);


/* addset: add an element to a set with words that match the first n characters,
 * at or below this node */
struct set_tnode *addset(struct set_tnode *node, char *word, int n)
{
    int cond;

    if (node == NULL) { /* a new set has arrived */
        node = set_talloc();
		node->right = node->left = NULL;
        node->tree = NULL;
        node->size = 1;
	    node->tree = addtree(node->tree, word);
    }
    else if ((cond = match(node->tree->word, word, n)) == 0) {
        node->tree = addtree(node->tree, word);   /* insert into matching set */
        (node->size)++;
    }
    else if (cond < 0)
        node->left = addset(node->left, word, n);
    else if (cond > 0)
        node->right = addset(node->right, word, n);

    return node;
}


/* set_tree_print: in-order print of the set of elements that match the first n
 * characters on p */
void set_tree_print(struct set_tnode *p, int n)
{
	if (p != NULL) {
		set_tree_print(p->left, n);

		if (p->size > 1) {
            printf("\033[34m""set '");
            for (int i = 0; i < n; ++i)
                putchar(p->tree->word[i]);
            printf("':\033[m\n");
		    tree_print(p->tree);
        }
        else {
            printf("\033[31m""not on set:\n""\033[m");
            tree_print(p->tree);
        }

		set_tree_print(p->right, n);
	}
}


/* talloc: make a set-tree node */
struct set_tnode *set_talloc(void)
{
    return (struct set_tnode *) malloc(sizeof(struct set_tnode));
}


/* check if a and b match at the first n characters */
unsigned match(char *a, char *b, int n)
{
    while (n-- != 0 && *a != '\0' && *b != '\0')
        if (*(a++) != *(b++))
            return a - b;

    return 0;
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


int getch(void);
int getch_skip(void);
void ungetch(int c);


/* getword: get next word of character from input */
int getword(char *word, int lim)
{
	int c;
	char *w = word;

	while (isspace(c = getch_skip()))
		;
	/* ignore blanks */

	if (c != EOF)
		*w++ = c;

	if (c == '#' || c == '_') {
		*w++ = c = getch_skip();
		--lim;
	}

	if (!(isalpha(c))) {
		*w = '\0';

		return c;
	}

	for (; --lim; w++)
		if (!(isalnum(*w = getch_skip())) && *w != '_') {
			ungetch(*w);
			break;
		}

	*w = '\0';

	return word[0];
}


/* get an input character, skipping if within a string */
int skip_string(void)
{
	int c = getch();

	if (c == '\"') {
		while ((c = getch()) != '\"')
			if (c == EOF)
				return c;

		/* verifica novamente se começou uma nova string/comentário */
		return getch_skip();
	}

	return c;
}


/* get an input character, skipping if within a string or comment */
int getch_skip(void)
{
	int c = skip_string();

	/* skips if withing a comment */
	if (c == '/') {

		if ((c = getch()) == '/')
			while ((c = getch()) != '\n');
		else if (c == '*')
			for (c = getch(); !(c == '*' & (c = getch()) == '/'); );
		else {
			ungetch(c);
			return '/';
		}

		/* verifica novamente se começou uma nova string/comentário */
		return getch_skip();
	}

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


/* tree_print: in-order print of the tree p */
void tree_print(struct tnode *p)
{
    if (p != NULL) {
        tree_print(p->left);
        printf("%4d %s\n", p->count, p->word);
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
