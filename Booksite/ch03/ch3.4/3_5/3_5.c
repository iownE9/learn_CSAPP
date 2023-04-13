/**
 * referenceURL: 配套习题 127
 * *
 * Environment: Linux
 * Compilation: gcc -Og -c 3_5.c
 * Compilation: gcc -Og -S 3_5.c
 * Compilation: objdump -d 3_5.o > 3_5.d
 * *
 * description:
 **/

void decode1(long *xp, long *yp, long *zp)
{
    long x = *xp;
    long y = *yp;
    long z = *zp;
    *yp = x;
    *zp = y;
    *xp = z;
}