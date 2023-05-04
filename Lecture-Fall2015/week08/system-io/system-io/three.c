#include <stdio.h>
#include <string.h>
#include <unistd.h>

//  strace -e trace=write ./three > /dev/null

int main(void)
{
    // Buffer only one line at a time.
    setvbuf(stdout, NULL, _IOLBF, 0);
    int n;
    printf("believe "); // not print a complete line
    n = write(STDOUT_FILENO, "in ", 3);
    printf("yourself! \n");

    // each string passed to printf is a complete line(ending with a ’\n’ character)
    printf("never\n");
    n = write(STDOUT_FILENO, "give\n", 5);
    printf("up! \n");

    printf("keep ");
    // fflush(stdout) causes the contents of the buffer to be printed immediately.
    fflush(stdout);
    n = write(STDOUT_FILENO, "it ", 3);
    printf("cool :) \n");

    printf("%d\n", n);
    return 0;
}
