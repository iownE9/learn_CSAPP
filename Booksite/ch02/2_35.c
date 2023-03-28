/**
 * referenceURL: 配套习题
 * referenceURL: zh-cn 68
 * *
 * Compilation: gcc 2_35.c -o 2_35
 * Execution:   ./2_35
 * *
 * description:
 **/

#include <stdio.h>

/* Determine whether arguments can be multiplied without overflow */
int tmult_ok(int x, int y)
{
    int p = x * y;
    /* Either x is zero, or dividing p by x gives y */
    return !x || p / x == y;
}

int main(void)
{

    return 0;
}