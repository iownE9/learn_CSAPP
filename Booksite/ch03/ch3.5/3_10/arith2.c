/**
 * referenceURL: 配套习题
 * *
 * Environment: Linux
 * Compilation: gcc -Og -c arith2.c
 * Compilation: gcc -Og -S arith2.c
 * Compilation: objdump -d arith2.o > arith2.d
 * *
 * description:
 **/

long arith2(long x, long y, long z)
{
    long t1 = x | y;
    long t2 = t1 >> 3;
    long t3 = ~t2;
    long t4 = z - t3;
    return t4;
}