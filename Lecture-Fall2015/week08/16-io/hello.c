#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("h");
    printf("e");
    printf("l");
    printf("l");
    printf("o");
    printf("\n");
    fflush(stdout);
    exit(0);
}

/*
> strace -e trace=write ./hello
write(1, "hello\n", 6hello
)                  = 6
+++ exited with 0 +++

*/