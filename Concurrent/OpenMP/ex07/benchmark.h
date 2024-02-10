#pragma once

#ifndef bool
typedef char bool;
#define true 1
#define false 0
#endif

/* Start the benchmark timer register from base execution. */
void start(const char *);

/* Starts next benchmark register. */
double next(const char *);

/* Stop the benchmark register. */
double stop();

/* Clear the benchmark registers. */
void clear();

/* Generates benchmark for registered executions. */
void benchmark(unsigned num_threads, bool clear);

/* Continues to next execution. */
void back(const char *name);
