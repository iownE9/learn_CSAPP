/**
 * referenceURL: zh-cn 125
 * *
 * Execution:   gcc -Og -S exchange.c
 * Execution:   gcc -Og -c exchange.c
 * Execution:   objdump -d exchange.o > exchange.d
 * Execution:   gcc -Og -S exchange.c -o exchange.s
 * *
 **/

long exchange(long *xp, long y)
{
    long x = *xp;
    *xp = y;
    return x;
}