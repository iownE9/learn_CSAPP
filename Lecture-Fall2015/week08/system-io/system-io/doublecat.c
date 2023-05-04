#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

static int Open(const char *pathname, int flags)
{
    assert(!(flags & O_CREAT));
    int fd = open(pathname, flags);
    if (fd == -1)
    {
        fprintf(stderr, "Error: cannot open '%s': %s\n", pathname,
                strerror(errno));
        exit(1);
    }

    return fd;
}

static int Close(int fd)
{
    if (close(fd) == -1)
    {
        fprintf(stderr, "Error reported while closing fd %d: %s\n", fd,
                strerror(errno));
        exit(1);
    }
    return 0;
}

static int print2(int fd1, int fd2)
{
    char c1, c2;
    int nbytes1, nbytes2;
    while ((nbytes1 = read(fd1, &c1, 1)) > 0 &&
           (nbytes2 = read(fd2, &c2, 1)) > 0)
    {
        printf("fd1=%d: %c\n"
               "fd2=%d: %c\n",
               fd1, c1, fd2, c2);
    }
    return 0;
}

int main(int argc, char **argv)
{
    int fd1, fd2;

    if (argc != 2)
    {
        printf("Usage: ./doublecat filename\n");
        return 1;
    }

    // CASE 1
    fd1 = Open(argv[1], O_RDONLY);
    fd2 = fd1;
    printf("One open call (fd1: %d, fd2: %d):\n", fd1, fd2);
    fflush(stdout);
    print2(fd1, fd1);
    Close(fd1);

    // CASE 2
    fd1 = Open(argv[1], O_RDONLY);
    fd2 = Open(argv[1], O_RDONLY);
    printf("Two open() calls (fd1: %d, fd2: %d):\n", fd1, fd2);
    fflush(stdout);
    print2(fd1, fd2);
    Close(fd1);
    Close(fd2);

    // CASE 3
    fd1 = Open(argv[1], O_RDONLY);
    dup2(fd1, fd2);
    printf("Copied with dup2 (fd1: %d, fd2: %d):\n", fd1, fd2);
    fflush(stdout);
    print2(fd1, fd2);
    Close(fd1);
    Close(fd2);

    return 0;
}
