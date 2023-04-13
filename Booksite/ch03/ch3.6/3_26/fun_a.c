/**
 * referenceURL: 配套习题
 * *
 * Environment: Linux
 * Compilation: gcc -Og -S fun_a.c
 * *
 * Compilation: gcc -O1 -S fun_a.c -o fun_a_O1.s
 * *
 * description:
 **/

long fun_a(unsigned long x)
{
    long val = 0;
    while (x)
    {
        val ^= x;
        x >>= 1;
    }
    return val & 0x1;
}