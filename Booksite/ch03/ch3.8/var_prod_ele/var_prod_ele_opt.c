/**
 * referenceURL: zh-cn 182
 * *
 * Compilation: gcc -Og -S var_prod_ele_opt.c
 * *
 * Compilation: gcc -O1 -S var_prod_ele_opt.c -o var_prod_ele_opt_O1.s
 * *
 * description:
 **/

int var_prod_ele_opt(long n, int A[n][n], int B[n][n], long i, long k)
{
    int *Arow = A[i];
    int *Bptr = &B[0][k];

    int result = 0;
    long j;

    for (j = 0; j < n; j++)
    {
        result += Arow[j] * *Bptr;
        Bptr += n;
    }

    return result;
}