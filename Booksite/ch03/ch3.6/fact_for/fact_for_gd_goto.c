/**
 * referenceURL: 配套习题解答 3_27
 * referenceURL: zh-cn
 * *
 * Compilation: gcc -Og -S fact_for_gd_goto.c
 * *
 * Compilation: gcc -O1 -S fact_for_gd_goto.c -o fact_for_gd_goto_O1.s
 * *
 * description:
 **/

long fact_for_gd_goto(long n)
{
    long i = 2;
    long result = 1;
    if (n <= 1)
        goto done;
loop:
    result += 1;
    i++;
    if (i <= n)
        goto loop;
done:
    return result;
}