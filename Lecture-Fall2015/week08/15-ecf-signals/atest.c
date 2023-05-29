#include "csapp.h"

/*

> gcc -c atest.c ; gcc atest.o csapp.o -o atest

*/

int main(int argc, char **argv)
{
    int N = 5;
    int pid;
    // for (int i = 0; i < N; i++)
    // {
    if ((pid = Fork()) == 0)
    { /* Child process */
        setpgid(0, 0);
        sleep(5);
        Execve("/bin/date", argv, NULL);
        printf("child\n");
        // }
    }

    printf("pid = %d\n", pid);

    if ((pid = Waitpid(pid, NULL, 0)) > 0)
    {
        printf(" wait pid = %d\n", pid);
    }

    printf("pid = %d\n", pid);
    return 0;
}
