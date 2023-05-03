#include "../csapp.h"

/* $begin waitprob1 */
/* $begin wasidewaitprob1 */
int main()
{
    int status;
    pid_t pid;

    printf("Hello\n");
    pid = Fork();
    printf("!pid = %d\n", !pid);

    if (pid != 0) // 父进程
    {
        if (waitpid(-1, &status, 0) > 0)
        {
            if (WIFEXITED(status) != 0)
                printf("exit or return %d\n", WEXITSTATUS(status));
        }
    }
    printf("Bye\n");
    exit(2);
}
/* $end waitprob1 */
/* $end wasidewaitprob1 */
