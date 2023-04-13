/**
 * referenceURL: 配套习题
 * *
 * Environment: Linux
 * Compilation: gcc -Og -c uremdiv.c
 * Compilation: gcc -Og -S uremdiv.c
 * Compilation: objdump -d uremdiv.o > uremdiv.d
 * *
 * description:
 **/

void uremdiv(unsigned long x, unsigned long y,
             unsigned long *qp, unsigned long *rp)
{
    unsigned long q = x / y;
    unsigned long r = x % y;
    *qp = q;
    *rp = r;
}