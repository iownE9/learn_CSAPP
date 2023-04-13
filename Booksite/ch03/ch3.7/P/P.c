/**
 * referenceURL: zh-cn 173
 * *
 * Environment: Linux
 * Compilation: gcc -Og -S P.c
 * *
 * Compilation: gcc -O1 -S P.c -o P_O1.s
 * *
 * description:
 **/

long P(long x, long y)
{
    long u = Q(y);
    long v = Q(x);
    return u + v;
}