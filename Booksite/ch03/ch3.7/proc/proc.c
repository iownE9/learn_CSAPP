/**
 * referenceURL: zh-cn 169
 * *
 * Environment: Linux
 * Compilation: gcc -Og -S proc.c
 * *
 * Compilation: gcc -O1 -S proc.c -o proc_O1.s
 * *
 * description:
 **/

void proc(long a1, long *a1p,
          int a2, int *a2p,
          short a3, short *a3p,
          char a4, char *a4p)
{
    *a1p += a1;
    *a2p += a2;
    *a3p += a3;
    *a4p += a4;
}
