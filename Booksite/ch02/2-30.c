/**
 * *
 * Environment: Linux
 * Compilation: gcc 2-30.c -o 2-30
 * Execution:   ./2-30
 * *
 * description:
 **/

#include <stdio.h>

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

int main(void)
{

    return 0;
}