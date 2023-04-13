/**
 * referenceURL: zh-cn 145
 * *
 * Environment: Linux
 * Compilation: gcc -Og -S absdiff.c
 * Compilation: gcc -O1 -S -fno-if-conversion absdiff.c
 * *
 * Compilation: gcc -O1 -S absdiff.c -o absdiff_O1.s
 * *
 * description:
 **/

long absdiff(long x, long y)
{
    long result;
    if (x < y)
        result = y - x;
    else
        result = x - y;
    return result;
}