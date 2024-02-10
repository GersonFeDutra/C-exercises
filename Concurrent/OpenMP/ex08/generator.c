#include <stdlib.h>
#include <stddef.h>

float *f_generate(size_t n, float max)
{
    float *f = malloc(sizeof(float) * n);

    for (float *p = f, *q = f + n; p != q; p++)
        // Read <https://stackoverflow.com/a/13409133> for reference
        *p = (float)rand() / (float)(RAND_MAX / max);

    return f;
}
