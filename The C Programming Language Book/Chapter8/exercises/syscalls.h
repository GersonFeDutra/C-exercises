#pragma once

#include <unistd.h>    // read, write, lseek, close, fork, exec, pipe, etc.
#include <fcntl.h>     // open, O_RDONLY, O_WRONLY, O_CREAT, O_TRUNC, fcntl()
#include <sys/types.h> // mode_t, off_t, pid_t, ssize_t
#include <sys/stat.h>  // file modes: S_IRUSR, S_IWUSR, etc.
#include <errno.h>     // error codes

#ifndef MYSTDIO_FLAGS
    #define MYSTDIO_FLAGS
    #define BUFSIZ 8192
    #define EOF (-1)
#endif

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
