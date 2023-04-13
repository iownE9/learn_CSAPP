/**
 * referenceURL: 配套习题
 * *
 * Environment: Linux
 * Compilation: gcc -Og -S fun_b.c
 * Compilation: gcc -O1 -S -fno-if-conversion fun_b.c
 * *
 * Compilation: gcc -O1 -S fun_b.c -o fun_b_O1.s
 * *
 * description:
 **/

long fun_b(unsigned long x)
{
    long val = 0;
    long i;
    for (i = 64; i != 0; --i)
    {
        val = (val << 1) | (x & 0x1);
        x >>= 1;
    }
    return val;
}