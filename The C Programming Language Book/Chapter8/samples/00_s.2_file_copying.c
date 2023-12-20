#include "syscalls.h"

main() /* copy input to output */
{
#ifdef ON_UNIX
    char buf[BUFSIZE];
    int n;

    while ((n = read(0, buf, BUFSIZE)) > 0)
        write(1, buf, n);
#else
    nuw();
#endif
}
