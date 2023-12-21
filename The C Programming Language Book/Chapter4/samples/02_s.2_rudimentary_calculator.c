#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 100


int main(void)
{
    double sum, atof(const char []);
    char line[MAXLINE];
    int getline_(char line[], int max);

    sum = 0;
    while (getline_(line, MAXLINE) > 0)
        printf("\t%g\n", sum += atof(line));

    return EXIT_SUCCESS;
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
