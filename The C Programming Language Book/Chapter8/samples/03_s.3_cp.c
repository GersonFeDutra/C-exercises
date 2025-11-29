#include "syscalls.h"

#define PERMS 0666 /* RW for owner, group, others */

// #ifdef ON_UNIX
// #include <fcntl.h>
// #endif
// #ifdef BSD
/* BSD (Berkley) systems */
// #include <sys/file.h> // alternative to fcntl
// #endif


void error(char *, ...);

/* cp: copy f1 to f2 */
int main(int argc, const char *argv[])
{
    int f1, f2, n; /* fX: file descriptors, n: buffered characters */
	char buf[BUFSIZ];

	if (argc != 3)
		error("Usage [cp]: %s from to", argv[0]);
	if ((f1 = open(argv[1], O_RDONLY, 0)) == -1)
		error("cp: can't open %s", argv[1]);
	if ((f2 = creat(argv[2], PERMS)) == -1)
		error("cp: can't create %s, mode %03o", argv[2], PERMS);

	while ((n = read(f1, buf, BUFSIZ)) > 0)
		if (write(f2, buf, n) != n)
			error("cp: write error on file %s", argv[2]);

	return EXIT_SUCCESS;
}


#include <stdio.h>
#include <stdarg.h>

/* error: print an error message and die */
void error(char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	fprintf(stderr, "error: ");
	vfprintf(stderr, fmt, args);
	fprintf(stderr, "\n");
	va_end(args);

	exit(EXIT_FAILURE);
}
