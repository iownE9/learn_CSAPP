/**
 * referenceURL: 配套习题
 * *
 * Compilation: gcc -Og -S fix_set_diag_opt.c
 * *
 * Compilation: gcc -O1 -S fix_set_diag_opt.c -o fix_set_diag_opt_O1.s
 * *
 * description:
 **/

#define N 16

typedef int fix_matrix[N][N];

/* Set all diagonal elements to val */
void fix_set_diag_opt(fix_matrix A, int val)
{
    int *Abase = &A[0][0];
    long i = 0;
    long iend = N * (N + 1);

    do
    {
        Abase[i] = val;
        i += (N + 1);
    } while (i != iend);
}