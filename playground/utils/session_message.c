#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define INVALID_FILE_ERROR 2
#define prerr(S, ARGS...) fprintf(stderr, "\033[31m" "Error: " S "\033[m" __VA_OPT__(,) ARGS)

/* rline: read a ramdom line from a file */
int main(int argc, const char *argv[])
{
    if (argc != 2) {
        prerr("No messages' source found!");
        return EXIT_FAILURE;
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        prerr("Invalid file path!\n");
        return INVALID_FILE_ERROR;
    }

    long random_long(long min, long max);

    fseek(fp, 0L, SEEK_END);
    long size = ftell(fp);

    fseek(fp, random_long(0L, size), SEEK_SET);
    
    int c;
    while (ftell(fp) != 0L && (c = fgetc(fp)) != '\n')
        fseek(fp, -2 * sizeof(char), SEEK_CUR); // roll back to start of line

    while ((c = fgetc(fp)) != EOF && c != '\n')
        putchar(c);

    putchar('\n');

    return EXIT_SUCCESS;
}



// Cryptographical safe long number generator:

//#include <stdio.h>
//#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

unsigned long xorshift(unsigned long state[static 1]) {
    unsigned long x = state[0];
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    state[0] = x;
    return x;
}

long random_long(long min, long max) {
    int urandom = open("/dev/urandom", O_RDONLY);
    unsigned long state[1];
    read(urandom, state, sizeof(state));
    close(urandom);
    unsigned long range = (unsigned long) max - min + 1;
    unsigned long random_value = xorshift(state) % range;
    return (long) (random_value + min);
}
