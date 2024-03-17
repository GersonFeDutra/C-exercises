#include "benchmark.h"
#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

static double _start;

typedef struct node {
    double time;
    const char *name;
    struct node *next;
}* List;
static struct info {
    List list;
    List tail;
    bool stopped;
} *info = NULL;

struct group_node {
    const char *name;
    struct info *list;
    struct group_node *next;
};
static struct {
    struct group_node *list;
    struct group_node *tail;
    double base_time;
} groups = {NULL, NULL, 0.0};
static unsigned using_groups = 0;

void start(const char * name)
{
    printf("%s time: ...", name);
    fflush(stdout);

    info = malloc(sizeof(struct info));
    info->stopped = true;

    // Check if a group exists (force creation)
    if (groups.list == NULL) {
        groups.tail = groups.list = malloc(sizeof(struct group_node));
        groups.tail->name = NULL; // Default
        groups.tail->list = info;
        groups.tail->next = NULL;
    }

    // Adds info node
    info->tail = info->list = malloc(sizeof(struct node));
    info->tail->name = name;
    info->tail->time = 0.0;
    info->tail->next = NULL;

    _start = MPI_Wtime();
    info->stopped = false;
}

void start_group(const char *name, const char *first)
{
    printf("Group %s:\n", name);

    start(first);
    groups.tail->name = name;
    using_groups = 1;
}

static double _group_total_time(struct group_node *g)
{
    double total = 0.0f;
    for (struct node *n = g->list->list; n != NULL; n = n->next)
        total += n->time;

    printf("Group [%s] total time: %.3f\n", g->name, total);

    return total;
}

double next(const char * name)
{
    double time = MPI_Wtime() - _start;

    printf("\b\b\b%g\n", time); // Elapsed time
    printf("%s time: ...", name);
    fflush(stdout);

    // Add a info node
    info->tail->time = time;
    info->tail = info->tail->next = malloc(sizeof(struct node));
    info->tail->name = name;
    info->tail->time = 0.0;
    info->tail->next = NULL;

    _start = MPI_Wtime();
    return time;
}

void next_group(const char *name, const char *next)
{
    if (!info->stopped)
        stop();

    // Calculate group time:
    struct group_node *n = groups.tail;
    groups.base_time = _group_total_time(n);

    printf("\nGroup %s:\n", name);

    start(next);

    // Add next group node
    groups.tail = malloc(sizeof(struct group_node));
    groups.tail->name = name;
    groups.tail->list = info;
    groups.tail->next = NULL;

    n->next = groups.tail;
}

double stop()
{
    double time = MPI_Wtime() - _start;

    printf("\b\b\b%g\n", time);

    info->tail->time = time;
    _start = 0.0;
    info->stopped = true;
    return time;
}

void back(const char *name)
{
    printf("%s time: ...", name);
    fflush(stdout);

    // Add next node
	info->tail = info->tail->next = malloc(sizeof(struct node));
	info->tail->name = name;
	info->tail->time = 0.0;
	info->tail->next = NULL;

	_start = MPI_Wtime();
    info->stopped = false;
}


void print_efficiency(double t_serial, double t_parallel, unsigned threads_used)
{
	double speedup = t_serial / t_parallel;
    printf("Speedup: %.4f\n", speedup);
	printf("Efficiency: %.4f\n", speedup / threads_used);
}

static void _benchmark_sequence(unsigned num_threads, bool clear)
{
    const char *fast_name = info->list->name;
    double serial_time;
    double fast_time;
    fast_time = serial_time = info->list->time;

	List next = info->list->next;

    if (clear)
        free(info->list);

	while (next != NULL) {
        printf("\n* %s *", next->name);
		double time = next->time;

		if (time <= fast_time) {
            fast_name = next->name;
            fast_time = time;
        }

        print_efficiency(serial_time, time, num_threads);

        info->list = next;
		next = next->next;

        if (clear)
            free(info->list);
	}

    printf("\nFastest: %s\n", fast_name);
}


static double _benchmark_group(unsigned num_threads, bool clear)
{
    double total = 0.0f;

    List next;
    for (List n = info->list; n != NULL; n = next) {
        total += next->time;
        printf("\t%s %g\n", n->name, n->time);

        next = n->next;
        if (clear)
            free(n);
    }

    return total;
}


void benchmark(unsigned num_threads, bool clear)
{
    if (!info->stopped)
        stop();

    printf("\n\nThreads used: %u\n", num_threads);

    if (using_groups) {
        double serial_time = groups.base_time;
        double fast_time = serial_time;
        const char *fast_name = groups.list->name;

        for (struct group_node *g = groups.list; g != NULL; g = g->next) {
            info = g->list;
            double total = 0.0;

            printf("Group [%s]:\n", g->name);
            double time = _benchmark_group(num_threads, clear);
            printf("\tTotal time: %g\n", time);

            if (g != groups.list)
                print_efficiency(serial_time, time, num_threads);

            if (time <= fast_time) {
                fast_name = g->name;
                fast_time = time;
            }
        }

        printf("\nFastest: %s\n", fast_name);
    }
    else
        _benchmark_sequence(num_threads, clear);
}

void clear()
{
    struct group_node *next_group;
    for (struct group_node *g = groups.list; g != NULL; g = next_group) {
        info = g->list;

        List next = info->list->next;

        free(info->list);

        while (next != NULL) {
            info->list = next;
            next = next->next;
            free(info->list);
        }

        next_group = g->next;
        free(g);
    }
}
