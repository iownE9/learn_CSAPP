/**
 * referenceURL: zh-cn 157
 * *
 * Environment: Linux
 * Compilation: gcc -Og -S fact_for.c
 * *
 * Compilation: gcc -O1 -S fact_for.c -o fact_for_O1.s
 * *
 * description:
 **/

long fact_for(long n)
{
    long i;
    long result = 1;
    for (i = 2; i <= n; i++)
        result *= i;
    return result;
}