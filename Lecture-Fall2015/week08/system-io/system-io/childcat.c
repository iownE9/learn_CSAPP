#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

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

static pid_t Fork(void)
{
    pid_t child = fork();
    if (child < 0)
    {
        perror("fork");
        exit(1);
    }
    return child;
}

int main(int argc, char **argv)
{
    char c;
    int fd, nbytes;

    if (argc != 2)
    {
        printf("Usage: ./childcat filename\n");
        return 1;
    }

    fd = Open(argv[1], O_RDONLY);
    int n;
    if (Fork())
    {
        // parent
        nbytes = read(fd, &c, 1);
        if (nbytes > 0)
            n = write(1, &c, nbytes);
        wait(NULL);
        // Ensure a final newline.
        c = '\n';
        n = write(1, &c, 1);
    }
    else
    {
        // child
        if (Fork())
        {
            // still child
            nbytes = read(fd, &c, 1);
            if (nbytes > 0)
                n = write(1, &c, nbytes);
            nbytes = read(fd, &c, 1);
            if (nbytes > 0)
                n = write(1, &c, nbytes);
            wait(NULL);
        }
        else
        {
            // grandchild
            nbytes = read(fd, &c, 1);
            if (nbytes > 0)
                n = write(1, &c, nbytes);
            nbytes = read(fd, &c, 1);
            if (nbytes > 0)
                n = write(1, &c, nbytes);
        }
    }

    // fd will be closed automatically when we exit.
    // Since we are only reading, we don't care about close errors.
    printf("\n n %d\n", n);
    return 0;
}
