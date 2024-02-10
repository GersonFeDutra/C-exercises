#include "benchmark.h"
#include <omp.h>
#include <stdlib.h>
#include <stdio.h>

static double _start;

typedef struct node {
    double time;
    const char *name;
    struct node *next;
}* List;
static struct {
    List list;
    List tail;
    bool stopped;
} info = {.stopped=true};

void start(const char * name)
{
    printf("Serial time: ...");
    fflush(stdout);

    info.tail = info.list = malloc(sizeof(struct node));
    info.tail->name = name;
    info.tail->time = 0.0;
    info.tail->next = NULL;

    _start = omp_get_wtime();
    info.stopped = false;
}

double next(const char * name)
{
    double time = omp_get_wtime() - _start;

    printf("\b\b\b%g\n", time);
    printf("%s time: ...", name);
    fflush(stdout);

    info.tail->time = time;

    info.tail = info.tail->next = malloc(sizeof(struct node));
    info.tail->name = name;
    info.tail->time = 0.0;
    info.tail->next = NULL;

    _start = omp_get_wtime();
    return time;
}

double stop()
{
    double time = omp_get_wtime() - _start;

    printf("\b\b\b%g\n", time);

    info.tail->time = time;
    _start = 0.0;
    info.stopped = true;
    return time;
}

void back(const char *name)
{
    printf("%s time: ...", name);
    fflush(stdout);

	info.tail = info.tail->next = malloc(sizeof(struct node));
	info.tail->name = name;
	info.tail->time = 0.0;
	info.tail->next = NULL;

	_start = omp_get_wtime();
    info.stopped = false;
}


void print_efficiency(double t_serial, double t_parallel, unsigned threads_used)
{
	double speedup = t_serial / t_parallel;
    printf("\nSpeedup: %.4f\n", speedup);
	printf("Efficiency: %.4f\n", speedup / threads_used);
}


void benchmark(unsigned num_threads, bool clear)
{
    if (!info.stopped)
        stop();

    printf("Threads used: %u\n", num_threads);

    double serial_time = info.list->time;
    double fast_time = serial_time;
    const char *fast_name = info.list->name;

	List next = info.list->next;

    if (clear)
        free(info.list);

	while (next != NULL) {
        printf("\n* %s *", next->name);
		double time = next->time;

		if (time <= fast_time) {
            fast_name = next->name;
            fast_time = time;
        }

        print_efficiency(serial_time, time, num_threads);

        info.list = next;
		next = next->next;

        if (clear)
            free(info.list);
	}

    printf("\nFastest: %s\n", fast_name);
}

void clear()
{
	List next = info.list->next;

    free(info.list);

	while (next != NULL) {
        info.list = next;
		next = next->next;
        free(info.list);
	}
}
