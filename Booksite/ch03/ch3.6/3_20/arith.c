/**
 * referenceURL: 配套习题
 * *
 * Environment: Linux
 * Compilation: gcc -Og -S arith.c
 * Compilation: gcc -O1 -S -fno-if-conversion arith.c
 * *
 * Compilation: gcc -O1 -S arith.c -o arith_O1.s
 * *
 * description:
 **/

#define OP /

long arith(long x)
{
    return x OP 8;
}