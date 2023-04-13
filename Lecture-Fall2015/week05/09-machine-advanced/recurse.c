/**
 * Compilation: gcc -Og -S recurse.c
 * Compilation: gcc -O1 -S recurse.c -o recurse_O1.s
 * *
 * Compilation: gcc recurse.c -o recurse
 * Execution:   ./recurse
 * *
 * description: Runaway Stack Example
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int recurse(int x)
{
    int a[1 << 15]; // 4*2^15 = 128 KiB
    printf("x = %d. a at %p\n", x, a);

    a[0] = (1 << 14) - 1;
    a[a[0]] = x - 1;
    if (a[a[0]] == 0)
        return -1;

    return recurse(a[a[0]]) - 1;
}

int main(int argc, char *argv[])
{
    // 不断递归调用，超过8MB
    int val = 67;

    if (argc > 1)
        val = strtol(argv[1], NULL, 0);

    recurse(val);

    return 0;
}