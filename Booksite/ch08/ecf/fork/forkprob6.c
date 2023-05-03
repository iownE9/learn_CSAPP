/* $begin forkprob6 */
#include "csapp.h"

void doit()
{
    if (Fork() == 0)
    {
        Fork();
        printf("hello\n");
        return; // 返回到 main
    }
    return;
}

int main()
{
    doit();
    printf("hello\n");
    exit(0);
}
/* $end forkprob6 */
