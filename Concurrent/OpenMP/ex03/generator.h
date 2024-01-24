#pragma once
#include <stddef.h>
/* Generate a list of random long from [0, max)*/
long *l_generate(size_t n, long max);

/* Generate a list of random integers from [0, max)*/
int *i_generate(size_t n, int max);
