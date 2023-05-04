#include "csapp.h"

int main()
{
    int fd;
    char c;

    fd = Open("foobar.txt", O_RDONLY, 0);

    if (Fork() == 0)
    {
        Read(fd, &c, 1);
        exit(0);
    }

    wait(NULL);
    Read(fd, &c, 1);

    printf("c = %c\n", c);

    Close(fd);
    exit(0);
}