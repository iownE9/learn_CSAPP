/**
 * referenceURL: zh-cn 129
 * *
 * Execution:   gcc -Og -S scale.c
 * Execution:   gcc -Og -c scale.c
 * Execution:   objdump -d scale.o > scale.d
 * *
 **/

long scale(long x, long y, long z)
{
    long t = x + 4 * y + 12 * z;
    return t;
}