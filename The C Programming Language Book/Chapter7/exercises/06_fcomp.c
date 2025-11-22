#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


char *f_gets(char *s, int n, FILE *iop);
int f_puts(char *s, FILE *iop);
int get_line(char *line, int max, FILE *iop);

bool compare(const char* s, const char* t);

/**
 * Write a program to compare two files, printing the first line where they differ.
 * @note Usage: ./fcomp file1 [file2]
 *       If file2 is not given, compare with stdin.
 *       Shows differ line from file1.
 **/
int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "\033[33mUsage: '%s' file1 [file2]\033[m\n", argv[0]);
        return EXIT_FAILURE;
    }
    char line_a[250];
    char line_b[250];
    FILE *file_a = fopen(argv[1], "r");
    FILE *file_b = argc > 2 ? fopen(argv[2], "r") : stdin;

    while (get_line(line_a, sizeof(line_a), file_a)
           && get_line(line_b, sizeof(line_b), file_b))
        if (!compare(line_a, line_b)) {
            fprintf(stderr, "\033[31m");
            f_puts(line_a, stdout);
            fprintf(stderr, "\033[m");
            return EXIT_FAILURE;
        }

    return EXIT_SUCCESS;
}

bool compare(const char* s, const char* t)
{
    for (const char *p = s, *q = t; *p && *q; p++, q++)
        if (*p != *q)
            return false;
    return true;
}


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
int get_line(char *line, int max, FILE *iop)
{
    if (f_gets(line, max, iop) == NULL)
        return 0;
    else
        return strlen(line);
}
