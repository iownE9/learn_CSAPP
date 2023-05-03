#include "../csapp.h"

void handler(int sig)
{
    return;
}

unsigned int snooze(unsigned int secs)
{
    unsigned int rc = sleep(secs);
    printf("Slept for %d of %d secs.\n", secs - rc, secs);
    return rc;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <secs>\n", argv[0]);
        exit(0);
    }

    if (signal(SIGINT, handler) == SIG_ERR)
    {
        unix_error("signal error\n");
    }

    (void)snooze(atoi(argv[1]));

    exit(0);
}

/*

steve@Steve ~/l/B/c/8_7 (main)> ./snooze 5
1
2
3
^CSlept for 2 of 5 secs.
4
5
steve@Steve ~/l/B/c/8_7 (main)>

*/