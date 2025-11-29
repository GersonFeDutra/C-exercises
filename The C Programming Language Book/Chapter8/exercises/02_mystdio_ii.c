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
#include "syscalls.h"
#define PERMS 0666 /* RW for owner, group, others */

/* fopen: open file, return file ptr */
FILE *fopen(char *name, char *mode)
{
    int fd;
    FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;

    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
        if (!(fp->readable || fp->writable))
            break;           /* found free slot */

    if (fp >= _iob + OPEN_MAX) /* no free slots */
        return NULL;

    if (*mode == 'w')
        fd = creat(name, PERMS);
    else if (*mode == 'a'){
        if ((fd = open(name, O_WRONLY, 0)) == -1)
            fd = creat(name, PERMS);
        lseek(fd, 0L, 2);
    }
    else
        fd = open(name, O_RDONLY, 0);

    if (fd == -1) /* couldn't access name */
        return NULL;
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
        if (fp->cnt == -1)
            fp->eof = true;
        else
            fp->err = false;

        fp->cnt = 0;
        return EOF;
    }

    return (unsigned char) *fp->ptr++;
}


FILE _iob[OPEN_MAX] = { /* stdin, stdout, stderr */
    { 0, (char *) 0, (char *) 0, .readable = true, false, false, false, false, 0},
    { 0, (char *) 0, (char *) 0, .readable = false, true, false, false, false, 1},
    { 0, (char *) 0, (char *) 0, .readable = true, false, true, false, false, 2},
};
#pragma endregion


#pragma region Example Main Program
#include "utils.h"

/** Rewrite fopen and _fillbuf with fields instead of explict bit operations.
 * Compare code size and execution speed.
 **/
// Ex.: cat
int main(int argc, char const *argv[])
{
    FILE *fp; /* File pointer */
    char c;   /* last character read */
    const char *prog = argv[0]; /* program name for errors */

    if (argc == 1) {
        warn("Usage: %s file1 [file2 ...]", prog);
        error("No file specified.");
    }
    else
        while (--argc > 0)
            if ((fp = fopen(*++argv, "r")) == NULL)
                error("'%s' can't open '%s'", prog, *argv);
            else {
                while ((c = getc(fp)) != EOF)
                    putc(c, stdout);
                close(fp);
            }
    if (ferror(stdout))
        error("'%s' failed writing to standard output.", prog);
    return EXIT_SUCCESS;
}
#pragma endregion
