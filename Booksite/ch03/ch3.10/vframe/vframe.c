/**
 * referenceURL: zh-cn 202
 * *
 * Compilation: gcc -Og -S vframe.c
 * Compilation: gcc -Og -fno-stack-protector -S vframe.c -o vframe_nop.s
 * *
 * Compilation: gcc -O1 -S vframe.c -o vframe_O1.s
 * *
 * description:
 **/

long vframe(long n, long idx, long *q)
{
    long i;
    long *p[n];
    p[0] = &i;

    for (i = 1; i < n; i++)
        p[i] = q;

    return *p[idx];
}