/**
 * referenceURL: 配套习题
 * *
 * Environment: Linux
 * Compilation: gcc -Og -c 3_9.c
 * Compilation: gcc -Og -S 3_9.c
 * Compilation: objdump -d 3_9.o > 3_9.d
 * *
 * description:
 **/

long shift_left4_rightn(long x, long n)
{
    x <<= 4;
    x >>= n;
    return x;
}