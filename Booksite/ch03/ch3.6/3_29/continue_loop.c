/**
 * referenceURL: 配套习题解答
 * referenceURL: zh-cn
 * *
 * Compilation: gcc -Og -S continue_loop.c
 * *
 * Compilation: gcc -O1 -S continue_loop.c -o continue_loop_O1.s
 * *
 * description:
 **/

int continue_loop()
{
    long sum = 0;
    long i;
    for (i = 0; i < 10; i++)
    {
        if (i & 1)
            continue;
        sum += i;
    }
    return sum;
}