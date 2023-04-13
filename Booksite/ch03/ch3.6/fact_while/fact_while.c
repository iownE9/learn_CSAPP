/**
 * referenceURL: zh-cn 153
 * *
 * Environment: Linux
 * Compilation: gcc -Og -S fact_while.c
 * *
 * Compilation: gcc -O1 -S fact_while.c -o fact_while_O1.s
 * *
 * description:
 **/

long fact_while(long n)
{
    long result = 1;
    while (n > 1)
    {
        result *= n;
        n = n - 1;
    }
    return result;
}