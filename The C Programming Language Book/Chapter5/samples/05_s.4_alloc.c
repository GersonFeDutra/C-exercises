#define ALLOCSIZE 10000 /* size of available space */

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


#include <stdio.h>

#define LEN1 10
#define LEN2 20
int main(void)
{
    void fill(char arr[], char n);
    char *arr1, *arr2;

    arr1 = alloc(LEN1);
    arr2 = alloc(LEN2);

    fill(arr1, LEN1);
    fill(arr2, LEN2);
    printf("%s\n", arr1);
    printf("%s\n", arr2);

    afree(arr2);
    afree(arr1);

    return 0;
}


void fill(char arr[], char n)
{
    for (int i = 0, to = n - 1; i < to; ++i)
        arr[i] = 'a' + i;

    arr[n] = '\0';
}
