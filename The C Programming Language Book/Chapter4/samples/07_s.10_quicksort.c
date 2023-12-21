#include <stdio.h>
#include <stdlib.h>


/* quicksort: sort v[left]...v[right] into increasing order.
 * this is not the fastest version of quick sort.
 * this method complexity: O(n²) */
void quicksort(int v[], int left, int right)
{
    int i, last;
    void swap(int v[], int i, int j);

    if (left >= right) /* do nothing if array contains */
        return;        /* fewer then two elements */

    swap(v, left, (left + right) / 2); /* move partition element to "v[0]" */
    last = left;

    for (i = left + 1; i <= right; i++) /* partition */
        if (v[i] < v[left])
            swap(v, ++last, i);

    swap(v, left, last); /* restore partition */
    quicksort(v, left, last - 1);
    quicksort(v, last + 1, right);
}


/* swap: interchange v[i] and v[j] */
void swap(int v[], int i, int j)
{
    int tmp;

    tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
}


int main(int argc, char const *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "\033[31mError: expected at least one integer as argument.\n\033[m");
        return EXIT_FAILURE;
    }
    int arr[argc - 1];

    for (int i = 1; i < argc; ++i)
        arr[i - 1] = atoi(argv[i]);

    quicksort(arr, 0, argc - 1);

    printf("%d", arr[0]);
    for (int i = 1; i < argc - 1; ++i)
        printf(" %d", arr[i]);
    putchar('\n');

    return EXIT_SUCCESS;
}
