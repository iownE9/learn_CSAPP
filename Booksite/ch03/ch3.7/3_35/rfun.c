/**
 * referenceURL: 配套习题
 * *
 * Environment: Linux
 * Compilation: gcc -Og -S rfun.c
 * *
 * Compilation: gcc -O1 -S rfun.c -o rfun_O1.s
 * *
 * description:
 **/

long rfun(unsigned long x)
{
    if (x == 0)
        return 0;
    unsigned long nx = x >> 2;
    long rv = rfun(nx);
    return rv + x;
}