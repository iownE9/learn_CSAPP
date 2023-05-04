#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 512

int main(int argc, char **argv)
{
    char buf[BUFFER_SIZE];
    int fd;
    ssize_t nbytes;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        return 1;
    }

    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        fprintf(stderr, "Error: cannot open %s: %s\n", argv[1],
                strerror(errno));
        return 1;
    }

    // FIXME: There's a bug on the next line! Can you fix it?
    // while ((nbytes = read(fd, buf, BUFFER_SIZE)) == BUFFER_SIZE)
    int n;
    while ((nbytes = read(fd, buf, BUFFER_SIZE)) > 0)
    {
        n = write(1, &buf, nbytes);
    }

    printf("n %d\n", n);
    close(fd);
    return 0;
}
