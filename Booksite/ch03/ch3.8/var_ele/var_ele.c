/**
 * referenceURL: zh-cn 181
 * *
 * Compilation: gcc -Og -S var_ele.c
 * *
 * Compilation: gcc -O1 -S var_ele.c -o var_ele_O1.s
 * *
 * description:
 **/

int var_ele(long n, int A[n][n], long i, long j)
{
    return A[i][j];
}