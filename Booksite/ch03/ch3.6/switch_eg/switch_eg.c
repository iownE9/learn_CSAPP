/**
 * referenceURL: zh-cn 160
 * *
 * Environment: Linux
 * Compilation: gcc -Og -S switch_eg.c
 * *
 * Compilation: gcc -O1 -S switch_eg.c -o switch_eg_O1.s
 * *
 * description:
 **/

void switch_eg(long x, long n,
               long *dest)
{
    long val = x;
    switch (n)
    {
    case 100:
        val *= 13;
        break;
    case 102:
        val += 10;
    /* Fall through */
    case 103:
        val += 11;
        break;
    case 104:
    case 106:
        val *= val;
        break;
    default:
        val = 0;
    }
    *dest = val;
}
