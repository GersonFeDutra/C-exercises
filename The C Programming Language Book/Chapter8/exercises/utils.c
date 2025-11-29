#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include "utils.h"


void error(char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	fprintf(stderr, "\033[31m""[error]: ");
	vfprintf(stderr, fmt, args);
	fprintf(stderr, "\033[m\n");
	va_end(args);

	exit(EXIT_FAILURE);
}

void warn(char * fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	fprintf(stderr, "\033[33m""[warning]: ");
	vfprintf(stderr, fmt, args);
	fprintf(stderr, "\033[m\n");
	va_end(args);
}
