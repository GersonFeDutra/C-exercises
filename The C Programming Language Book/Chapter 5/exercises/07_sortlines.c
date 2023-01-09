#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 1000     /* max length of any input line */
#define MAXLINES 5000    /* max #lines to be sorted */
char *lineptr[MAXLINES]; /* pointers to text lines */

int readlines(char *lineptr[], int nlines, char buf[]);
void writelines(char *lineptr[], int nlines);

void quicksort(char *lineptr[], int left, int right);


/* sort input lines
 * Rewrite readlines to store lines in an array supplied by main,
 * rather than calling alloc to maintain storage.
 * How much faster is the program?
 * - Answer: given that we only check for storage once now, this version is a bit faster.
 *   if alloc was done dynamically, this could be probably be significantly faster,
 *   since we would not need to ask the system to load more storage.
 *   But it also uses more space, since the allocation is done statically once. */
int main(void)
{
    int nlines; /* number of input lines read */
    char text[MAXLEN * MAXLINES];

    if ((nlines = readlines(lineptr, MAXLINES, text)) >= 0) {
        quicksort(lineptr, 0, nlines - 1);
        writelines(lineptr, nlines);

        return EXIT_SUCCESS;
    }
    else {
        fprintf(stderr, "\033[31m""Error: input too big to sort.\033[m\n");

        return EXIT_FAILURE;
    }
}


int get_line(char *, int);
char *alloc(int);


/* readlines: read input lines: requires a single char buffer, must be large enough */
int readlines(char *lineptr[], int maxlines, char buf[])
{
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = get_line(line, MAXLEN)) > 0)
        if (nlines >= maxlines)
            return -1;
        else {
            p = buf;
            buf += len;
            line[len - 1] = '\0'; /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
        }

    return nlines;
}


/* writelines: write output lines */
// void writelines(char *lineptr[], int nlines)
// {
//     int i;
// 
//     for (i = 0; i < nlines; i++)
//         printf("%s\n", lineptr[i]);
// 
// }


/* writelines: write output lines: pointer version */
void writelines(char *lineptr[], int nlines)
{
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
}


/* Read a line into string `s`, return length. */
int get_line(char s[], int lim)
{
	int c, i;

	for (i = 0; (i < lim - 1) && ((c = getchar()) != EOF) && (c != '\n'); ++i)
		s[i] = c;

	if (c == '\n')
		s[i++] = c;

	s[i] = '\0';

	return i;
}


/* quicksort: sort v[left]...v[right] into increasing order.
 * this is not the fastest version of quick sort.
 * this method complexity: O(n²) */
void quicksort(char *v[], int left, int right)
{
    int i, last;
    void swap(char *v[], int i, int j);

    if (left >= right) /* do nothing if array contains */
        return;        /* fewer then two elements */

    swap(v, left, (left + right) / 2); /* move partition element to "v[0]" */
    last = left;

    for (i = left + 1; i <= right; i++) /* partition */
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);

    swap(v, left, last); /* restore partition */
    quicksort(v, left, last - 1);
    quicksort(v, last + 1, right);
}


/* swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j)
{
    char *tmp;

    tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
}
