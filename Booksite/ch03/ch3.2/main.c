/**
 * *
 * Environment: Linux
 * Compilation: gcc -Og main.c mstore.c -o prog
 * Compilation: objdump -d prog > prog.d
 * *
 * description: zh-cn p116
 **/

#include <stdio.h>

void multstore(long, long, long *);

int main()
{
    long d;
    multstore(2, 3, &d);
    printf("2 * 3 --> %ld\n", d);
    return 0;
}

long mult2(long a, long b)
{
    long s = a * b;
    return s;
}