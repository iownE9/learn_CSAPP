#include "csapp.h"

void sigint_handler(int sig) /* SIGINT handler */
{
    // 这个变成 SIGINT 的处理程序
    // 故在此期间 相同的 SIGINT ctrl-c 直接被舍弃
    printf("So you think you can stop the bomb with ctrl-c, do you?\n");
    sleep(2);
    printf("Well...");
    fflush(stdout);
    sleep(1);
    printf("OK. :-)\n");
    exit(0);
}

int main()
{
    /* Install the SIGINT handler */
    if (signal(SIGINT, sigint_handler) == SIG_ERR)
        unix_error("signal error");

    /* Wait for the receipt of a signal */
    pause();

    return 0;
}
