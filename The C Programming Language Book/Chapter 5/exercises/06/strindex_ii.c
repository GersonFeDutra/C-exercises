#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000 /* maximum input line length */

int getline_(char s[], int lim);


/* strindex: return pointer of t in s, or NULL if not found */
const char *strindex(const char *s, const char t[])
{
    for (const char *u; *s != '\0'; s++) {
        int i;

        for (u = s, i = 0; t[i] != '\0' && *u == t[i]; u++, i++);

        if (i > 0 && t[i] == '\0')
            return u;
    }

    return NULL;
}


/* find all lines matching pattern */
int main(int argc, char const *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "\033[31m""Error! No string pattern passed as argument!\033[m\n");

        return -1;
    }

    char line[MAXLINE];
	int found = 0;

    while (getline_(line, MAXLINE) > 0)
        if (strindex(line, argv[1]) != NULL) {
            printf("%s", line);
            found++;
        }

    return found;
}


/* getline_: get line into s, return length */
int getline_(char s[], int lim)
{
    int c, i;

    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;

    if (c == '\n')
        s[i++] = c;

    s[i] = '\0';

    return i;
}
