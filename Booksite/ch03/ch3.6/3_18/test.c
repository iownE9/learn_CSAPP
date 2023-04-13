/**
 * referenceURL: 配套习题
 * *
 * Environment: Linux
 * Compilation: gcc -Og -c test.c
 * Compilation: gcc -Og -S test.c
 * Compilation: objdump -d test.o > test.d
 * *
 * description:
 **/

long test(long x, long y, long z)
{
    long val = x + y + z;
    if (x < -3)
    {
        if (y < z)
            val = y * x;
        else
            val = y * z;
    }
    else if (x > 2)
        val = x * z;
    return val;
}