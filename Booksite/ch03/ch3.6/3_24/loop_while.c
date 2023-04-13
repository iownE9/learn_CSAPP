/**
 * referenceURL: 配套习题
 * *
 * Environment: Linux
 * Compilation: gcc -Og -S loop_while.c
 * *
 * Compilation: gcc -O1 -S loop_while.c -o loop_while_O1.s
 * *
 * description:
 **/

long loop_while(long a, long b)
{
    long result = 1;
    while (a < b)
    {
        result = (b + a) * result;
        a = a + 1;
    }
    return result;
}