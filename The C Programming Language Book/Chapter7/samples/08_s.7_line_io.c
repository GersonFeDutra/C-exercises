#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* f_gets: get at most n chars from iop */
char *f_gets(char *s, int n, FILE *iop)
{
    register int c;
    register char *cs;

    cs = s;
    while (--n > 0 && (c = getc(iop)) != EOF)
        if ((*cs++ = c) == '\n')
            break;
    *cs = '\0';

    return (c == EOF && cs == s) ? NULL : s;
}


/* f_puts: put string s on file iop */
int f_puts(char *s, FILE *iop)
{
    int c;

    while (c = *s++)
        putc(c, iop);

    return ferror(iop) ? EOF : 0;
}


/* get_line: read a line, return length */
int get_line(char *line, int max)
{
    if (f_gets(line, max, stdin) == NULL)
        return 0;
    else
        return strlen(line);
}


int main(void)
{
    char line[250];

    fprintf(stdout, "\033[34m");
    while (get_line(line, sizeof(line)))
        f_puts(line, stdout);
    fprintf(stdout, "\033[m");

    return EXIT_SUCCESS;
}
