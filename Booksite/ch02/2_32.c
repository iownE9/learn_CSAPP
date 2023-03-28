/**
 * referenceURL: 配套习题
 * referenceURL: zh-cn 65
 * *
 * Compilation: gcc 2_32.c -o 2_32
 * Execution:   ./2_32
 * *
 * description:
 **/

#include <stdio.h>

#include <limits.h>

/* Determine whether arguments can be added without overflow */
int tadd_ok(int x, int y)
{
    int sum = x + y;
    int neg_over = x < 0 && y < 0 && sum >= 0;
    int pos_over = x >= 0 && y >= 0 && sum < 0;

    // return !neg_over && !pos_over;
    return !(neg_over || pos_over);
}
// This function should return 1 if arguments x and y can be added without causing overflow

/* Determine whether arguments can be subtracted without overflow */
int tsub_ok(int x, int y)
{
    if (y == INT_MIN && x < 0)
        return 1;

    return tadd_ok(x, -y);
}

int main(void)
{

    return 0;
}