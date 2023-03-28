/**
 * referenceURL: 配套习题解答
 * *
 * Compilation: gcc 2_36.c -o 2_36
 * Execution:   ./2_36
 * *
 * description:
 **/

#include <stdio.h>
#include <stdint.h>

// Determine whether the arguments can be multiplied without overflow
int tmult_ok(int x, int y)
{
    // Compute product without overflow
    int64_t pll = (int64_t)x * y;
    // see if casting to int preserves value
    return pll == (int)pll;
}
int main(void)
{

    return 0;
}