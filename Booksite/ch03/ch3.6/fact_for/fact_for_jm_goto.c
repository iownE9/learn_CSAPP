/**
 * referenceURL: zh-cn 157
 * *
 * Environment: Linux
 * Compilation: gcc -Og -S fact_for_jm_goto.c
 * Compilation: gcc -O1 -S -fno-if-conversion fact_for_jm_goto.c
 * *
 * Compilation: gcc -O1 -S fact_for_jm_goto.c -o fact_for_jm_goto_O1.s
 * *
 * description:
 **/
long fact_for_jm_goto_jm_goto(long n)
{
    long i = 2;
    long result = 1;
    goto test;
loop:
    result *= i;
    i++;
test:
    if (i <= n)
        goto loop;
    return result;
}
