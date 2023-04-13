/**
 * referenceURL: 配套习题
 * *
 * Compilation: gcc -Og -S intlen.c
 * Compilation: gcc -Og -fno-stack-protector -S intlen.c -o intlen_nop.s
 * *
 * Compilation: gcc -Og -c intlen.c
 * Compilation: objdump -d intlen.o > intlen.d
 * *
 * Compilation: gcc -O1 -S intlen.c -o intlen_O1.s
 * *
 * description:
 **/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int len(char *s)
{
    return strlen(s);
}

void iptoa(char *s, long *p)
{
    long val = *p;
    sprintf(s, "%ld", val);
}

int intlen(long x)
{
    long v;
    char buf[12];
    v = x;
    iptoa(buf, &v);
    return len(buf);
}