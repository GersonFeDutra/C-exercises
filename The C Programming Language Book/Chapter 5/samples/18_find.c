#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000 /* maximum input line length */

int get_line(char *s, unsigned int lim);
const char *strindex(const char *s, const char t[]);


/* find: print lines that match pattern from 1st arg */
int main(int argc, char const *argv[])
{
	if (argc < 2) {
        fprintf(stderr, "\033[33m""Usage: find pattern.\033[m\n");
		fprintf(stderr, "\033[31mError! No string pattern passed as argument!\033[m\n");

		return -1;
	}

	char line[MAXLINE];
	int found = 0;
	setbuf(stdout, NULL);

	while (get_line(line, MAXLINE) != EOF) {
        const char *at, *p;
		if ((at = strindex(line, argv[1])) != NULL) {

			for (p = line; p != at; ++p)
				putchar(*p);

			fprintf(stderr, "\033[32m");
			for (const char *c = argv[1]; *p == *c && *c != '\0'; c++)
				putchar(*p++);
			fprintf(stderr, "\033[m");

			printf("%s", p);
			found++;
		}
    }

	return found;
}


/* Read a line into string `s`. return last read char or EOF: pointer version */
int get_line(char *s, unsigned int lim)
{
	int c;

	for (; lim && ((c = getchar()) != EOF) && (c != '\n'); --lim)
		*s++ = c;

	if (c == '\n')
		*s++ = c;

	*s = '\0';

    return c;
}


/* strindex: return pointer of t in s, or NULL if not found */
const char *strindex(const char *s, const char t[])
{
    for (const char *u; *s != '\0'; s++) {
        int i;

        for (u = s, i = 0; t[i] != '\0' && *u == t[i]; u++, i++);

        if (i > 0 && t[i] == '\0')
            return s;
    }

    return NULL;
}
