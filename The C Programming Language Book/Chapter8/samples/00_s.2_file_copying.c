#include "syscalls.h"


main() /* copy input to output */
{
    char buf[BUFSIZ];
    int n;

    while ((n = read(STDIN_FILENO, buf, BUFSIZ)) > 0)
        write(1, buf, n);
}
