#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000 /* maximum input line length */

int getline_(char s[], int lim);
int strindex(const char s[], const char t[]);


/* find all lines matching pattern */
int main(int argc, char const *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "\033[31mError! No string pattern passed as argument!\033[m\n");

        return -1;
    }

    char line[MAXLINE];
	int found = 0;

    while (getline_(line, MAXLINE) > 0)
        if (strindex(line, argv[1]) >= 0) {
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


/* strindex: return index of t in s, -1 if none */
int strindex(const char s[], const char t[])
{
    int i, j, k;

    for (i = 0; s[i] != '\0'; i++) {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++);

        if (k > 0 && t[k] == '\0')
            return i;
    }

    return -1;
}
