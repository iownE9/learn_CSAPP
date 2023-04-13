/**
 * referenceURL: zh-cn 188
 * *
 * Compilation: gcc -Og -S uu2double.c
 * Compilation: gcc -O1 -S uu2double.c -o uu2double_O1.s
 * *
 * Compilation: gcc uu2double.c -o uu2double
 * Execution:   ./uu2double
 * *
 * description:
 **/
/* $begin show-bytes */
#include <stdio.h>
/* $end show-bytes */
#include <stdlib.h>
#include <string.h>
/* $begin show-bytes */

typedef unsigned char *byte_pointer;

double uu2double(unsigned word0, unsigned word1)
{
    union
    {
        double d;
        unsigned u[2];
    } temp;

    temp.u[0] = word0;
    temp.u[1] = word1;

    return temp.d;
}

void show_bytes(byte_pointer start, size_t len)
{
    size_t i;
    for (i = 0; i < len; i++)
        printf(" %.2x", start[i]); // line:data:show_bytes_printf
    printf("\n");
}

unsigned long double2bits(double d)
{
    union
    {
        double d;
        unsigned long u;
    } temp;

    temp.d = d;
    return temp.u;
}

int main(int argc, char *argv[])
{
    // 比特位不变
    double x = uu2double(0x7f35, 0x6598a);
    show_bytes((byte_pointer)&x, sizeof(double));

    // 比特位不变
    unsigned long x1 = double2bits(x);
    show_bytes((byte_pointer)&x1, sizeof(unsigned long));

    // 比特位变化 x 对应的实数是0 0赋值给u
    unsigned long u = (unsigned long)x;
    show_bytes((byte_pointer)&u, sizeof(long));
}