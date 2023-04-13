/**
 * referenceURL: 配套习题
 * *
 * Environment: Linux
 * Compilation: gcc -Og -S loop_while2.c
 * *
 * Compilation: gcc -O1 -S loop_while2.c -o loop_while2_O1.s
 * *
 * description:
 **/

long loop_while2(long a, long b)
{
    long result = b;
    while (b > 0)
    {
        result = result * a;
        b = b - a;
    }
    return result;
}