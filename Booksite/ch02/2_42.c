/**
 * referenceURL: 配套习题解答
 * referenceURL: zh-cn74
 * *
 * Compilation: gcc 2_42.c -o 2_42
 * Execution:   ./2_42
 * *
 * description:
 **/

#include <stdio.h>
#include <stdint.h>

int32_t div16(int32_t x)
{
    // Compute bias to be either 0 (x>=0) or 15 (x<0)
    int bias = (x >> 32) & 0xF;
    return (x + bias) >> 4;

    // return (x < 0 ? x + (1 << 4) - 1 : x) >> 4;
}

int main(void)
{

    return 0;
}