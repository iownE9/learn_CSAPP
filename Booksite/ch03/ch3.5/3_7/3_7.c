/**
 * referenceURL: 配套习题 130
 * *
 * Environment: Linux
 * Compilation: gcc -Og -c 3_7.c
 * Compilation: gcc -Og -S 3_7.c
 * Compilation: objdump -d 3_7.o > 3_7.d
 * *
 * description:
 **/

short scale3(short x, short y, short z)
{
    short t = 5 * x + 2 * y + 8 * z;
    return t;
}