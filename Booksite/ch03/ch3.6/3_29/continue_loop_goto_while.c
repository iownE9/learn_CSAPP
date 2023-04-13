/**
 * referenceURL: 配套习题解答
 * referenceURL: zh-cn
 * *
 * Compilation: gcc -Og -S continue_loop_goto_while.c
 * *
 * Compilation: gcc -O1 -S continue_loop_goto_while.c -o continue_loop_goto_while_O1.s
 * *
 * description:
 **/

int continue_loop_goto_while()
{
    long sum = 0;
    long i = 0;
    while (i < 10)
    {
        if (i & 1)
            goto update;
        sum += i;
    update:
        i++;
    }

    return sum;
}