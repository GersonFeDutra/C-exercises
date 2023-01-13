#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000    /* max #lines to be sorted */
char *lineptr[MAXLINES]; /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void quicksort(void *v[], int left, int right,
        int (*comp)(const void *, const void *), unsigned short reverse);
int numcmp(const char *, const char *);
int strfcmp(const char *s, const char *t);


/* sort input lines (lexigraphically or numerically)
 * Add the option -f to fold upper and lower case together,
 * so that case distinctions are not made during sorting;
 * for example, a and A compare equal. */
int main(int argc, char *argv[]) {
    int nlines;  /* number of input lines read */
    int numeric = 0;    /* 1 if numeric sort */
    int reverse = 0;    /* 1 if reverse sort */
    int fold_case = 0;  /* 1 if fold "case sensitivity"  */

    while (--argc)
        if (**++argv == '-')
            while (*++*argv)
                switch (**argv) {
                    case 'n': numeric = 1; break;
                    case 'r': reverse = 1; break;
                    case 'f': fold_case = 1; break;
                    default:
                        fprintf(stderr, "\033[33m""Warning: Unknow option %s.\033[m\n", *argv);
                        break;
                }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        quicksort((void **)lineptr, 0, nlines - 1,
                (int (*)(const void *, const void *))(
                        numeric ? numcmp : (fold_case ? strfcmp : strcmp) ), reverse);
        writelines(lineptr, nlines);

        return EXIT_SUCCESS;
    }
    else {
        fprintf(stderr, "\033[31m""Error: input too big to sort.\033[m\n");

        return EXIT_FAILURE;
    }
}


static short reverse_sort;


/* quicksort: sort v[left]...v[right] into increasing order.
 * this is not the fastest version of quick sort.
 * this method complexity: O(n²) */
void quicksort(void *v[], int left, int right,
        int (*comp)(const void *, const void *), unsigned short reverse)
{
    void _quicksort(void *v[], int left, int right, int (*comp)(const void *, const void *));

    reverse_sort = reverse ? 1 : -1;
    _quicksort(v, left, right, comp);
}


/* quick sort routine called by the helper method above */
void _quicksort(void *v[], int left, int right, int (*comp)(const void *, const void *))
{
    int i, last;
    void swap(void *v[], int, int);

    if (left >= right) /* do nothing if array contains */
        return;        /* fewer then two elements */

    swap(v, left, (left + right) / 2); /* move partition element to "v[0]" */
    last = left;

    for (i = left + 1; i <= right; i++) /* partition */
        if (comp(v[i], v[left]) * reverse_sort > 0)
            swap(v, ++last, i);

    swap(v, left, last); /* restore partition */
    _quicksort(v, left, last - 1, comp);
    _quicksort(v, last + 1, right, comp);
}


/* swap: interchange v[i] and v[j] */
void swap(void *v[], int i, int j)
{
    void *tmp;

    tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
}


/* strfcmp: return <0 if s<t, 0 if s==t, >0 if s>t: case insensitive
 * folds the case of the letters, that is, eg.: a = A */
int strfcmp(const char *s, const char *t)
{
    for (; *s == *t || (*s >= 'a' && *s <= 'z' && *s - 'a' + 'A' == *t)
            || (*s >= 'A' && *s <= 'Z' && *s - 'A' + 'a' == *t); s++, t++)
        if (*s == '\0')
            return 0;

    return *s - *t;
}


/* numcmp: compare s1 and s2 numerically */
int numcmp(const char *s1, const char *s2)
{
    double v1 = atof(s1), v2 = atof(s2);

    return (v1 - v2) / abs(v1 - v2);
    /* equivalent to the comparisons above: */
    // if (v1 < v2)
        // return -1;
    // else if (v1 > v2)
        // return 1;
    // return 0;
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


#define MAXLEN 1000     /* max length of any input line */

int get_line(char *, int);
char *alloc(int);


/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = get_line(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else {
            line[len - 1] = '\0'; /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
        }

    return nlines;
}


/* writelines: write output lines: pointer version */
void writelines(char *lineptr[], int nlines)
{
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
}


#define ALLOCSIZE MAXLINES * MAXLEN /* size of available space */

static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf;  /* next free position */


char *alloc(int n)  /* returns pointer to n characters */
{
    if (allocbuf + ALLOCSIZE - allocp >= n) { /* it fits */
        allocp += n;
        return allocp - n; /* old p */
    }
    else /* not enough room */
        return 0;
}


void afree(char *p) /* free storage pointed to by p */
{
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
}
