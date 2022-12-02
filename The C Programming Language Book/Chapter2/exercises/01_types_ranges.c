#include <float.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define TYPES_N 7

/* Write a program to determine the ranges of `char`, `short`, `int`, and `long` variables,
 * both signed and unsigned, by printing appropriate values from standard headers.
 * Determine the ranges of the various floating-point types.
 */
int main(void)
{
	struct type {
		char name[12];
		long double min;
		long double max;
	};
	struct type types[] = {
		{"char", CHAR_MIN, CHAR_MAX},
		{"short", SHRT_MIN, SHRT_MAX},
		{"int", INT_MIN, INT_MAX},
		{"long", LONG_MIN, LONG_MAX},
		{"float", FLT_MIN, FLT_MAX},
		{"double", DBL_MIN, DBL_MAX},
		{"long double", LDBL_MIN, LDBL_MAX},
	};

	printf("Type ranges:\n\n");
	printf("%12s | %14s | %14s\n",
            "Type", "Min", "Max");

	for (int i = 0; i < 12 + 2 * 14 + 6; ++i)
		putchar('-');

	printf("\n");
	for (int i = 0; i < TYPES_N; ++i)
		if (types[i].min < INT_MIN || types[i].max > INT_MAX)
			printf("%12s | %14Le | %14Le\n", types[i].name, types[i].min, types[i].max);
		else
			printf("%12s | %14.0Lf | %14.0Lf\n", types[i].name, types[i].min, types[i].max);

	return 0;
}
