/**
 * referenceURL: 配套习题
 * *
 * Environment: Linux
 * Compilation: gcc -Og -S dw_loop.c
 * *
 * Compilation: gcc -O1 -S dw_loop.c -o dw_loop_O1.s
 * *
 * description:
 **/

long dw_loop(long x)
{
    long y = x * x;
    long *p = &x;
    long n = 2 * x;
    do
    {
        x += y;
        (*p)++;
        n--;
    } while (n > 0);
    return x;
}