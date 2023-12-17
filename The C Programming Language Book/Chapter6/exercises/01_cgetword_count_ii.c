#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 100

struct key {
    const char *word;
    int count;
} keytab[] = {
	{ "#define", 0 },  { "#else", 0 },    { "#if", 0 },      { "#ifdef", 0 },
	{ "#include", 0 }, { "#pragma", 0 },  { "#undef", 0 },
    { "auto", 0 },     { "break", 0 },    { "case", 0 },     { "char", 0 },
    { "const", 0 },    { "continue", 0 }, { "default", 0 },  { "do", 0 },
    { "double", 0 },   { "else", 0 },	  { "enum", 0 },	 { "extern", 0 },
    { "float", 0 },    { "for", 0 },      { "goto", 0 },     { "if", 0 },
    { "int", 0 },	   { "long", 0 },     { "register", 0 }, { "return", 0 },
    { "short", 0 },    { "signed", 0 },   { "sizeof", 0 },   { "static", 0 },
    { "struct", 0 },   { "switch", 0 },   { "typedef", 0 },  { "union", 0 },
    { "unsigned", 0 }, { "void", 0 },     { "volatile", 0 }, { "while", 0 },
}; /* structure of type key, and keytab: an array of keys initialized subsequently */
// The keywords are stored in increasing order so we can use a binary search to search then.

int getword(char *, int);
int binsearch(const char *, struct key *, int);

/* count C keywords
 * our version of getword does not properly handle underscores, string constants,
 * comments, or preprocessor control lines. Write a better version */
int main(void)
{
	int n;
	char word[MAXWORD];

	#define NKEYS (sizeof keytab / sizeof(struct key))
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]) || word[0] == '#')
			if ((n = binsearch(word, keytab, NKEYS)) >= 0)
				keytab[n].count++;

	for (n = 0; n < NKEYS; n++)
		if (keytab[n].count > 0)
			printf("%4d %s\n",
					keytab[n].count, keytab[n].word);

	return EXIT_SUCCESS;
}


int getch(void);
int getch_skip(void);
void ungetch(int c);


/* getword: get next word of character from input */
int getword(char *word, int lim)
{
	int c;
	char *w = word;

	while (isspace(c = getch_skip()));
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


/* binsearch: find word in tab[0]...tab[n-1] */
int binsearch(const char *word, struct key tab[], int n)
{
	int cond;
	int low, high, mid;

	low = 0;
	high = n - 1;
	while (low <= high) {
		mid = (low + high) / 2;

		if ((cond = strcmp(word, tab[mid].word)) < 0)
			high = mid - 1;
		else if (cond > 0)
			low = mid + 1;
		else
			return mid;
	}

	return -1; /* no match */
}


#define TRUE 1
#define FALSE 0

static char buf;                      /* buffer for ungetch */
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
