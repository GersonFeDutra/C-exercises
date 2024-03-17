#pragma once
#include <stdlib.h>

#define max(A, B) ((A) > (B) ? (A) : (B))
#define rand_range(MIN, MAX) (rand() % ((MAX) - (MIN)) + (MIN))

/* msleep(): Sleep for the requested number of milliseconds. */
int msleep(long msec);

/* Starting random number generator */
void randomize();