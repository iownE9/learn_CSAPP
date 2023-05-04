#include "csapp.h"

int main(int argc, char *argv[])
{
    int fd1;
    int s = getpid() & 0x1;
    char c1, c2;
    char *fname = argv[1];

    fd1 = Open(fname, O_RDONLY, 0);
    Read(fd1, &c1, 1);

    if (fork())
    {
        /* Parent */
        sleep(s);
        Read(fd1, &c2, 1);
        printf("Parent: c1 = %c, c2 = %c\n", c1, c2);
    }
    else
    {
        /* Child */
        sleep(1 - s);
        Read(fd1, &c2, 1);
        printf("Child: c1 = %c, c2 = %c\n", c1, c2);
    }
    return 0;
}

/*
> ./ffiles2 abcde.txt
Child: c1 = a, c2 = b
Parent: c1 = a, c2 = c
> ./ffiles2 abcde.txt
Parent: c1 = a, c2 = b
Child: c1 = a, c2 = c

fork 前 fd 实例化，父子进程共享相同的打开文件表集合

*/
