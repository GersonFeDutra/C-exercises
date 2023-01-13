#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINES 5000    /* max #lines to be sorted */
char *lineptr[MAXLINES]; /* pointers to text lines */

int readlines(char *lineptr[], int n, unsigned short dir);
void writelines(char *lineptr[], int n);

void quicksort(void *v[], int left, int right,
        int (*comp)(const void *, const void *), unsigned short reverse);
int numcmp(const char *, const char *);
int strfcmp(const char *, const char *);


/* sort input lines (lexigraphically or numerically)
 * Add the -d ("directory order") option, which makes comparison only on
 * letters, numbers and blanks. Make sure it works in conjunction with -f */
int main(int argc, const char *argv[]) {
    enum options {
        NONE, NUMERIC = 1, REVERSE = 2, FOLD_CASE = 4, DIRECTORY = 8
    } option = NONE;
    int nlines;  /* number of input lines read */

    while (--argc)
        if (**++argv == '-')
            while (*++*argv)
                switch (**argv) {
                    case 'n': option |= NUMERIC;   break; /* numeric sort */
                    case 'r': option |= REVERSE;   break; /* reverse sort */
                    case 'f': option |= FOLD_CASE; break; /* case insensitive */
                    case 'd': option |= DIRECTORY; break;
                            /* letters, numbers, ., -, _ and blanks only */
                    default:
                        fprintf(stderr, "\033[33m""Warning: Unknow option %s.\033[m\n", *argv);
                        break;
                }

    if ((nlines = readlines(lineptr, MAXLINES, option & DIRECTORY)) >= 0) {
        quicksort((void **)lineptr, 0, nlines - 1,
                (int (*)(const void *, const void *))(
                    (option & NUMERIC) ? numcmp : (
                        (option & FOLD_CASE) ? strfcmp : strcmp) ),
                (option & REVERSE));
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


#include <ctype.h>

#define MAXLEN 1000     /* max length of any input line */

int get_line(char *, int);
int get_dir(char *, int);
char *alloc(int);


/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines, unsigned short dir)
{
    int (*get)(char *, int) = dir ? get_dir : get_line;
    int len, nlines, n = 0;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = get(line, MAXLEN)) != 0) {
        n++;
        if (len < 0)
            fprintf(stderr, "\033[33m""Warning: line \n#%d: %s\n\tis not a valid file name. "
                    "Skipping...\033[m\n", n, line);
        else if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else {
            line[len - 1] = '\0'; /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }

    return nlines;
}


/* Read a line into string `s`, return length.
 * return negative length if `s` is not a file name. */
int get_dir(char s[], int lim)
{
	int c, i, isdir = 1;

	for (i = 0; (i < lim - 1) && ((c = getchar()) != EOF) && (c != '\n'); ++i) {
        s[i] = c;

        if (!isalpha(c) && !isdigit(c) && !isblank(c) && c != '.' && c != '_' && c != '-')
            isdir = -1;
    }

	if (c == '\n')
		s[i++] = c;

	s[i] = '\0';

	return i * isdir;
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
