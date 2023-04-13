/**
 * referenceURL: zh-cn 150
 * *
 * Environment: Linux
 * Compilation: gcc -Og -S fact_do_goto.c
 * *
 * Compilation: gcc -O1 -S fact_do_goto.c -o fact_do_goto_O1.s
 * *
 * description:
 **/

long fact_do_goto(long n)
{
    long result = 1;
loop:
    result *= n;
    n = n - 1;
    if (n > 1)
        goto loop;
    return result;
}