/**
 * referenceURL: zh-cn 150
 * *
 * Environment: Linux
 * Compilation: gcc -Og -S fact_do.c
 * *
 * Compilation: gcc -O1 -S fact_do.c -o fact_do_O1.s
 * *
 * description:
 **/
long fact_do(long n)
{
    long result = 1;
    do
    {
        result *= n;
        n = n - 1;
    } while (n > 1);
    return result;
}