#include "syscalls.h"
#include "utils.h"

typedef int file_descriptor;

#define PERMS 0666 /* RW for owner, group, others */

const char *prog; /* program name for errors */
//char *current;  /* current file name being processed */


// TODO -> Benchmark
/** cat: concatenate files: version 3
 * Rewrite the program cat from Chapter 7 using read, write, open and close
 * instead of their standard library equivalents. Perform experiments to
 * determine the relative speeds of the two versions.
 **/
int main(int argc, char const *argv[])
{
    file_descriptor fd; 
    void filecopy(file_descriptor, file_descriptor);
    prog = argv[0];
    //current = "<standard output>";

    if (argc == 1) /* no args: copy standard input */
        filecopy(STDIN_FILENO, STDOUT_FILENO);
    else
        while (--argc > 0)
            if ((fd = open(*++argv, O_RDONLY, 0)) == -1)
                error("'%s' can't open '%s'", prog, *argv);
            else {
                filecopy(fd, STDOUT_FILENO);
                close(fd);
            }
    return EXIT_SUCCESS;
}


/* filecopy: copy file using descriptors */
void filecopy(file_descriptor in, file_descriptor out)
{
    ssize_t n;
	char buf[BUFSIZ];

	while ((n = read(in, buf, BUFSIZ)) > 0)
		if (write(out, buf, n) != n)
			error("'%s' failed to write on stdout", prog);
			//error("'%s' write error on file '%s'", prog, current);
}
