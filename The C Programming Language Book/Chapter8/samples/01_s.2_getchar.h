#pragma once

#include "syscalls.h"


/* getchar: unbuffered single character input */
int getchar(void)
{
    char c;

    return (read(STDIN_FILENO, &c, 1) == 1) ? (unsigned char) c : EOF;
}
