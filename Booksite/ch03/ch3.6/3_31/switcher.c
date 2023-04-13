/**
 * referenceURL: 配套习题
 * *
 * Environment: Linux
 * Compilation: gcc -Og -S switcher.c
 * *
 * Compilation: gcc -O1 -S switcher.c -o switcher_O1.s
 * *
 * description:
 **/

void switcher(long a, long b, long c, long *dest)
{
    long val;
    switch (a)
    {
    case 5: /* Case A */
        c = b ^ 15;
    /* Fall through */
    case 0: /* Case B */
        val = 112 + c;
        break;
    case 2: /* Case C */
    case 7: /* Case D */
        val = (c + b) << 2;
        break;
    case 4: /* Case E */
        val = a;
        break;
    default:
        val = b;
    }
    *dest = val;
}