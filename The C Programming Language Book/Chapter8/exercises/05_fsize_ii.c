#include <sys/types.h> // dev_t, ino_t
#include <sys/stat.h>  // stat (inod information) and file description flags
#include <dirent.h>    // Dirent, opendir, readdir, closedir
#include <limits.h>    // PATH_MAX

/* log and information passing */
#include <stdio.h>
#include <string.h>
#include <time.h>

// Requires at least one variadic argument
#define printerr(S, ...) \
    fprintf(stderr, "\033[31m" S "\033[m\n", __VA_ARGS__)
        // note that ARGS is an alias to __VA_ARGS__
// C++ version
/* #define printerr(S, ARGS...) \
         fprintf(stderr, "\033[31m" S "\033[m\n" __VA_OPT__(,) ARGS) */


typedef struct dirent Dirent;


/* dirwalk: apply fcn to all files in dir */
void dirwalk(char *dir, void (*fcn)(char *))
{
    // Better to use `pathconf` in modern systems
    // FILENAME_MAX is just the max length of a filename (not their full path)
    char name[FILENAME_MAX];
    Dirent *dp;
    DIR *dfd;

    if ((dfd = opendir(dir)) == NULL) {
        printerr("dirwalk: can't open %s", dir);
        return;
    }
    while ((dp = readdir(dfd)) != NULL) {
        if (strcmp(dp->d_name, ".") == 0
            || strcmp(dp->d_name, "..") == 0)
                continue; /* skip self and parent */

        if (strlen(dir) + strlen(dp->d_name) + 2 > sizeof(name))
            printerr("dirwalk: name %s/%s too long", dir, dp->d_name);
        else {
            sprintf(name, "%s/%s", dir, dp->d_name);
            (*fcn)(name);
        }
    }

    closedir(dfd);
}

/* fsize: print size of file "name" */
void fsize(char *name)
{
    struct stat stbuf;

    if (stat(name, &stbuf) == -1) {
		printerr("fsize: can't access %s", name);
        return;
	}

    if ((stbuf.st_mode & __S_IFMT) == __S_IFDIR)
        dirwalk(name, fsize);

    char mode[11];
    // turn mode in drwxrwxrwx format
    sprintf(mode, "%c%c%c%c%c%c%c%c%c",
        (stbuf.st_mode & S_IRUSR) ? 'r' : '-',
        (stbuf.st_mode & S_IWUSR) ? 'w' : '-',
        (stbuf.st_mode & S_IXUSR) ? 'x' : '-',
        (stbuf.st_mode & S_IRGRP) ? 'r' : '-',
        (stbuf.st_mode & S_IWGRP) ? 'w' : '-',
        (stbuf.st_mode & S_IXGRP) ? 'x' : '-',
        (stbuf.st_mode & S_IROTH) ? 'r' : '-',
        (stbuf.st_mode & S_IWOTH) ? 'w' : '-',
        (stbuf.st_mode & S_IXOTH) ? 'x' : '-');
    mode[10] = '\0';

    // dates
    char dt_created[17];
    strftime(dt_created, sizeof(dt_created), "%d/%m/%Y %H:%M", localtime(&stbuf.st_ctime));
    char dt_modified[17];
    strftime(dt_modified, sizeof(dt_modified), "%d/%m/%Y %H:%M", localtime(&stbuf.st_mtime));

    if (stbuf.st_size <= (off_t)(1e4))
        printf("%s %8ld B  %s - %s %s\n", mode, stbuf.st_size, dt_created, dt_modified, name);
    else if (stbuf.st_size <= (off_t)(1e7))
        printf("%s %8ld KB %s - %s %s\n", mode, stbuf.st_size / 1024, dt_created, dt_modified, name);
    else if (stbuf.st_size <= (off_t)(1e10))
        printf("%s %8ld MB %s - %s %s\n", mode, stbuf.st_size / (1024 * 1024), dt_created, dt_modified, name);
    else
        printf("%s %8ld GB %s - %s %s\n", mode, stbuf.st_size / (1024 * 1024 * 1024), dt_created, dt_modified, name);
}


#pragma region Main Program
#include "syscalls.h"

void fsize(char *);
void dirwalk(char *, void (*fcn)(char *));

/** print file name
 * Modify the fsize program to print the other information contained in the inode entry.
 **/
int main(int argc, char **argv)
{
    if (argc == 1) /* default: current directory */
        fsize(".");
    else
        while (--argc > 0)
            fsize(*++argv);

    return 0;
}
#pragma endregion
