#define MYSTDIO_FLAGS
#define NULL ((void *)(0))
#define EOF (-1)
#define BUFSIZ 8192
#define OPEN_MAX 20 /* max #files open at once */
#define true 1
#define false 0

typedef struct _iobuf {
    int cnt;    /* characters left */
    char *ptr;  /* next character position */
    char *base; /* location of a buffer */

    /* flags: access modes and error codes */
    unsigned readable : 1;   /* file open for reading */
    unsigned writable : 1;   /* file open for writing */
    unsigned unbuffered : 1; /* file is unbuffered */
    unsigned eof : 1;        /* EOF has occurred on this file */
    unsigned err : 1;      /* error occurred on this file */

    int fd;     /* file descriptor */
} FILE;

extern FILE _iob[OPEN_MAX]; /* input/output buffer */

#define stdin   (&_iob[0])
#define stdout  (&_iob[1])
#define stderr  (&_iob[2])

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define feof(p)     ((p)->eof)
#define ferror(p)   ((p)->err)
#define fileno(p)   ((p)->fd)

#define getc(p)    (--(p)->cnt >= 0 ? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x, p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x), p))
#define getchar()  getc(stdin)
#define putchar(x) putc((x), stdout)


#pragma region Definitions
#include <stdlib.h>
#include "syscalls.h"
#define PERMS 0666 /* RW for owner, group, others */

/* fopen: open file, return file ptr */
FILE *fopen(const char *name, const char *mode)
{
    int fd;
    FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;

    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
        if (!(fp->readable || fp->writable))
            break;             /* found free slot */

    if (fp >= _iob + OPEN_MAX) /* no free slots */
        return NULL;

    if (*mode == 'w')
        fd = creat(name, PERMS);
    else if (*mode == 'a') {
        if ((fd = open(name, O_WRONLY, 0)) == EOF)
            fd = creat(name, PERMS);
        lseek(fd, 0L, 2);
    }
    else
        fd = open(name, O_RDONLY, 0);
    if (fd == EOF) /* couldn't access name */
        return NULL;
    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    fp->readable = (*mode == 'r');
    fp->writable = !fp->readable;

    return fp;
}


int fflush(FILE *fp)
{
    if (!fp->writable || fp->err || fp->eof)
        return EOF;

    #pragma region Write out the buffer
    // assert(fp->cnt >= 0 && fp->cnt <= BUFSIZ);
    ssize_t to_write = (ssize_t)(fp->ptr - fp->base); /* bytes in buffer */
    ssize_t total_written = 0;

    while (total_written < to_write) {
        ssize_t w = write(fp->fd, fp->base + total_written, to_write - total_written);
        if (w <= 0) {
            if (errno == EINTR)
                continue; /* retry on interrupt */
            /* if write returned 0 (rare) treat as error */
            fp->err = true;
            return EOF;
        }
        total_written += w;
    }
    #pragma endregion

    fp->ptr = fp->base;
    fp->cnt = BUFSIZ;
    return 0;
}


int fclose(FILE *fp)
{
    int err = fflush(fp);
    err = close(fp->fd) == EOF ? EOF : err;
    fp->err = fp->eof = fp->unbuffered = fp->writable = fp->readable = false;

    #pragma region Clear FILE *
    free(fp->base);
    fp->base = fp->ptr = NULL;
    fp->cnt = 0;
    #pragma endregion

    return err;
}

// #include "syscall.h"

/* _fillbuf: allocate and fill input buffer */
int _fillbuf(FILE *fp)
{
    int bufsize;

    if (!fp->readable || fp->eof || fp->err)
        return EOF;

    bufsize = (fp->unbuffered) ? 1 : BUFSIZ;

    if (fp->base == NULL) /* no buffer yet */
        if ((fp->base = (char *) malloc(bufsize)) == NULL)
            return EOF; /* can't get buffer */

    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);

    if (--fp->cnt < 0) {
        // If read return 0, then treat as EOF
        if (fp->cnt == -1)
            fp->eof = true;
        else
            fp->err = true;

        fp->cnt = 0;
        return EOF;
    }

    return (unsigned char) *fp->ptr++;
}


int _flushbuf(int c, FILE *fp)
{
    if (!fp->writable || fp->err || fp->eof)
        return EOF;

    #pragma region Write Unbuffered
    if (fp->unbuffered) {
        if (write(fp->fd, &c, 1) != 1) {
            fp->err = true;
            return EOF;
        }
        return c;
    }
    #pragma endregion

    #pragma region New Buffer
    if (fp->base == NULL) { /* no buffer yet */
        if ((fp->base = (char *) malloc(BUFSIZ)) == NULL) {
            fp->err = true;
            return EOF;
        }
        fp->ptr = fp->base;
        fp->cnt = BUFSIZ; // free space
    }
    #pragma endregion

    #pragma region Write out the buffer
    // assert(fp->cnt >= 0 && fp->cnt <= BUFSIZ);
    if (fp->cnt == 0) { /* buffer full: flush */
        ssize_t to_write = (ssize_t)(fp->ptr - fp->base); /* bytes in buffer */
        ssize_t total_written = 0;

        while (total_written < to_write) {
            ssize_t w = write(fp->fd, fp->base + total_written, to_write - total_written);
            if (w <= 0) {
                if (errno == EINTR)
                    continue; /* retry on interrupt */
                /* if write returned 0 (rare) treat as error */
                fp->err = true;
                return EOF;
            }
            total_written += w;
        }
        /* reset buffer */
        fp->ptr = fp->base;
        fp->cnt = BUFSIZ;
    }
    #pragma endregion

    // simply put the character in the buffer
    --fp->cnt;
    return *(fp->ptr++) = c;
}


FILE _iob[OPEN_MAX] = { /* stdin, stdout, stderr */
    { 0, (char *) 0, (char *) 0, true, false, false, false, false, 0},
    { 0, (char *) 0, (char *) 0, false, true, false, false, false, 1},
    { 0, (char *) 0, (char *) 0, false, true, true, false, false, 2},
};
#pragma endregion


#pragma region Example Main Program
/** Design and write _flushbuf, fflush, and fclose. **/
// Ex.: cat
int main(int argc, char *argv[])
{
    FILE *fp; /* File pointer */
    char c;   /* last character read */
    const char *prog = argv[0]; /* program name for errors */

    if (argc == 1) {
        //warn("Usage: %s file1 [file2 ...]", prog);
        //error("No file specified.");
        return EXIT_FAILURE;
    }
    else
        while (--argc > 0)
            if ((fp = fopen(*++argv, "r")) == NULL) {
                //error("'%s' can't open '%s'", prog, *argv);
                char msg[] = "\033[31m""Error: '";
                for (char *p = msg; *p; p++)
                    putc(*p, stderr);
                for (const char *p = prog; *p; p++)
                    putc(*p, stderr);
                char msg2[] = "' can't open '";
                for (char *p = msg2; *p; p++)
                    putc(*p, stderr);
                for (char *p = *argv; *p; p++)
                    putc(*p, stderr);
                char msg3[] = "'\033[0m\n";
                for (char *p = msg3; *p; p++)
                    putc(*p, stderr);
            }
            else {
                while ((c = getc(fp)) != EOF)
                    putc(c, stdout);
                fflush(stdout);
                fclose(fp);
            }
    if (ferror(stdout))
        return EXIT_FAILURE;
        //error("'%s' failed writing to standard output.", prog);
    return EXIT_SUCCESS;
}
#pragma endregion
