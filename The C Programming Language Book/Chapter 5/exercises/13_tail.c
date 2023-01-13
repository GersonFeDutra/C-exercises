#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define DEF_LN 10   /* default number of lines to read */


int readllines(char *lineptr[], int lines, int *at);
void writellines(char *lineptr[], int nlines, int from, int size);


/* Write the program tail, which prints the last n lines of its input.
 * By default, n is 10, let us say, but it can be changed by an optional
 * argument, so that `tail -n` prints the last n lines.
 * The program should behave rationally no matter how unreasonable the input or the value of n.
 * Write the program so it makes best use of available storage; lines should be stored as
 * in the sorting program of Section 5.6, not in a two-dimensional array of fixed size. */
int main(int argc, char const *argv[])
{
    unsigned lines = DEF_LN; /* number of input lines to read */

    if (argc > 1) {
        if (argv[1][0] == '-' && isdigit(argv[1][1]))
            lines = atoi(argv[1] + 1);
        else
            fprintf(stderr, "\033[33m""Invalid command line argument.\n"
                    "Expects -n where n is the number of lines to output.\n"
                    "Fallback to default: %d.\033[m\n", lines);
    }

    char *lineptr[lines]; /* pointers to text lines */
    int at, read;

    if ((read = readllines(lineptr, lines, &at)) >= 0) {
        writellines(lineptr, read, at, lines);

        return EXIT_SUCCESS;
    }
    else {
        fprintf(stderr, "\033[31m""Error: Exceeded memory limit!\033[m\n");
        writellines(lineptr, -read, at, lines);

        return EXIT_FAILURE;
    }
}


#define MAXLEN 1000     /* max length of any input line */

size_t get_line(char s[], size_t lim);
char *alloc(size_t n);
void afree(size_t n);


/* readllines: read the last input lines.
 * returns the #of lines saved, and store the position of the last one in 'at'
 * returns a negative number if the memory limit was reached
 * subsequent lines are stored cyclically in 'lineptr'. */
int readllines(char *lineptr[], int lines, int *at)
{
    size_t len, lens[lines];
    int nlines, first;
    char *p, line[MAXLEN];

    for (*at = first = nlines = 0; (len = get_line(line, MAXLEN)) > 0; *at = (*at + 1) % lines) {
        if (nlines < lines)
            nlines++;
        else {
            afree(lens[first++]);
            first %= lines;
        }
        if ((p = alloc(len)) == NULL)
            return -nlines;

        line[len - 1] = '\0'; /* delete newline */
        strcpy(p, line);
        lineptr[*at] = p;
    }

    return nlines;
}


/* writelines: write the last n output lines pointed by 'lineptr'
 * starting at 'from' index cyclically */
void writellines(char *lineptr[], int nlines, int from, int size)
{
    for (from = (size + from - (nlines - 1)) % size; nlines > 1; --nlines, from = ++from % size)
        printf("%s\n", lineptr[from]);
}


/* Read a line into string `s`, return length. */
size_t get_line(char s[], size_t lim)
{
    size_t i;
	int c;

	for (i = 0; (i < lim - 1) && ((c = getchar()) != EOF) && (c != '\n'); ++i)
		s[i] = c;

	if (c == '\n')
		s[i++] = c;

	s[i] = '\0';

	return i;
}


#define ALLOCSIZE MAXLEN * DEF_LN * 100 /* size of available space */

char allocbuf[ALLOCSIZE];  /* storage for alloc */
static char *alloc_fp = allocbuf; /* first occupied position */
static char *alloc_np = allocbuf; /* next free position */
static size_t stored = 0;


/* returns pointer to n characters.
 * allocation is done in queue-mode (first-in, first-out). */
char *alloc(size_t n)
{
    if (ALLOCSIZE - stored < n)
        return 0; /* not enough room */
    else { /* it fits */
        char *oldp = alloc_np;

        alloc_np = allocbuf + (alloc_np - allocbuf + n) % ALLOCSIZE;
        return oldp;
    }
}

 /* requires amount of previously requested memory to free positionally using fifo */
void afree(size_t n)
{
    if (n > 0 && n <= stored)
        alloc_fp = allocbuf + (alloc_fp - allocbuf + n) % ALLOCSIZE;
}
