/**
 * referenceURL: zh-cn 157
 * *
 * Environment: Linux
 * Compilation: gcc -Og -S fact_for_while.c
 * *
 * Compilation: gcc -O1 -S fact_for_while.c -o fact_for_while_O1.s
 * *
 * description:
 **/

long fact_for_while_while(long n)
{
    long i = 2;
    long result = 1;
    while (i <= n)
    {
        result *= i;
        i++;
    }
    return result;
}