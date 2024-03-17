#pragma once
#include <stddef.h>
/* Generate a list of random float from [0.0f, max)*/
float *f_generate(size_t n, float max);

/* Generate a list of random double from [0.0, max)*/
double *d_generate(size_t n, double max);

void d_generate_at(double *at, size_t n, double max);
