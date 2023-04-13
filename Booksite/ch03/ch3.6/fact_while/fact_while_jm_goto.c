/**
 * referenceURL: zh-cn 153
 * *
 * Environment: Linux
 * Compilation: gcc -Og -S fact_while_jm_goto.c
 * *
 * Compilation: gcc -O1 -S fact_while_jm_goto.c -o fact_while_jm_goto_O1.s
 * *
 * description:
 **/
long fact_while_jm_goto(long n)
{
    long result = 1;
    goto test;
loop:
    result *= n;
    n = n - 1;
test:
    if (n > 1)
        goto loop;
    return result;
}