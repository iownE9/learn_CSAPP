/**
 * *
 * Environment: Linux
 * Compilation: gcc -Og -S mstore.c
 *
 * Compilation: gcc -Og -c mstore.c
 * Compilation: objdump -d mstore.o > mstore.d
 * *
 * description: zh-cn p115
 **/

long mult2(long, long);

void multstore(long x, long y, long *dest)
{
    long t = mult2(x, y);
    *dest = t;
}
