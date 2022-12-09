#include <stdio.h>
#include <stdlib.h>


/* shellsort:  sort v[0]...v[n-1] */
void shellsort(int v[], int n)
{
    int gap, i, j, tmp;

    for (gap = n / 2; gap > 0; gap /= 2)
        for (i = gap; i < n; i++)
            for (j = i - gap; j >= 0 && v[j] > v[j + gap]; j -= gap) {
                tmp = v[j];
                v[j] = v[j + gap];
                v[j + gap] = tmp;
            }
}


int main(int argc, char const *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "\033[33mNenhum valor indicado! Esperado uma lista de números inteiros.\033[m\n");
        return EXIT_SUCCESS;
    }

    const int len = argc - 1;
    int v[len];

    for (int i = 0; i < len; ++i)
        v[i] = atoi(argv[i + 1]);

    shellsort(v, len);

    for (int i = 0; i < len - 1; ++i)
        printf("%d ", v[i]);

    printf("%d\n", v[len - 1]);

    return EXIT_SUCCESS;
}
