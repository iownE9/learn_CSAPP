/**
 * referenceURL: 配套习题
 * *
 * Environment: Linux
 * Compilation: gcc -Og -c cond.c
 * Compilation: gcc -Og -S cond.c
 * Compilation: objdump -d cond.o > cond.d
 * *
 * description:
 **/

void cond(long a, long *p)
{
    if (p && *p < a)
        *p = a;
}