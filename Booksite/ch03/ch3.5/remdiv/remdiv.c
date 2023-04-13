/**
 * referenceURL: zh-cn 134
 * *
 * Execution:   gcc -Og -S remdiv.c
 * Execution:   gcc -Og -c remdiv.c
 * Execution:   objdump -d remdiv.o > remdiv.d
 * *
 * description:
 **/

void remdiv(long x, long y,
            long *qp, long *rp)
{
    long q = x / y;
    long r = x % y;
    *qp = q;
    *rp = r;
}