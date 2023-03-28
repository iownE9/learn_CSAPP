/**
 * *
 * Environment: Linux
 * Compilation: gcc 2-10_11.c -o 2-10_11
 * Execution:   ./2-10_11
 * *
 * description: 配套习题
 **/

#include <stdio.h>

void inplace_swap(int *x, int *y)
{
    // fix bug
    if (x == y)
        return;

    *y = *x ^ *y; /* Step 1 */
    *x = *x ^ *y; /* Step 2 */
    *y = *x ^ *y; /* Step 3 */
}

void reverse_array(int a[], int cnt)
{
    int first, last;
    for (first = 0, last = cnt - 1;
         first <= last;
         first++, last--)
        inplace_swap(&a[first], &a[last]);
}

int main(void)
{
    int a[5] = {1, 2, 3, 4, 5};
    reverse_array(a, 5);
    for (int i = 0; i < 5; i++)
        printf("%d ", a[i]);
    return 0;
}