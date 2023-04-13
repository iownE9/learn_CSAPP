/**
 * referenceURL: zh-cn 182
 * *
 * Compilation: gcc -Og -S var_prod_ele.c
 * *
 * Compilation: gcc -O1 -S var_prod_ele.c -o var_prod_ele_O1.s
 * *
 * description:
 **/

/* Compute i,k of variable matrix product */
int var_prod_ele(long n, int A[n][n], int B[n][n], long i, long k)
{
    long j;
    int result = 0;

    for (j = 0; j < n; j++)
        result += A[i][j] * B[j][k];

    return result;
}