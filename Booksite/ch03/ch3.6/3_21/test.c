/**
 * referenceURL: 配套习题
 * *
 * Environment: Linux
 * Compilation: gcc -Og -S test.c
 * Compilation: gcc -O1 -S -fno-if-conversion test.c
 * *
 * Compilation: gcc -O1 -S test.c -o test_O1.s
 * *
 * description:
 **/

long test(long x, long y)
{
    long val = 8 * x;
    if (y > 0)
    {
        if (x < y)
            val = y - x;
        else
            val = x & y;
    }
    else if (y <= -2)
        val = x + y;
    return val;
}
