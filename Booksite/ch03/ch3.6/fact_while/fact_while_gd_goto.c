/**
 * referenceURL: zh-cn 154
 * *
 * Environment: Linux
 * Compilation: gcc -Og -S fact_while_gd_goto.c
 * *
 * Compilation: gcc -O1 -S fact_while_gd_goto.c -o fact_while_gd_goto_O1.s
 * *
 * description:
 **/

long fact_while_gd_goto_gd_goto(long n)
{
    long result = 1;
    if (n <= 1)
        goto done;
loop:
    result *= n;
    n = n - 1;
    if (n != 1)
        goto loop;
done:
    return result;
}