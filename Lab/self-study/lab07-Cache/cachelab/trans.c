/*
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/*
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded.
 */
char transpose_submit_desc[] = "Transpose submission";
/*
Your performance score for each matrix size scales linearly with the number of misses
    • 32 × 32: 8 points if m < 300, 0 points if m > 600
    • 64 × 64: 8 points if m < 1, 300, 0 points if m > 2, 000
    • 61 × 67: 10 points if m < 2, 000, 0 points if m > 3, 000

    详见 trans_note.txt
    (s=5, E=1, b=5)
    32 块, 每块 8 int */
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    /*  Size of sub-matrix depends on cache block size,
        cache size, input matrix size*/
    int sub;
    switch (M)
    {
    case 32:
        // misses:344
        sub = 8;
        break;
    case 64:
        // misses:1892
        sub = 4;
        break;
    case 61:
        // misses:1951
        sub = 17;
        break;
    default:
        sub = 8;
        break;
    }

    int m, n;
    int i = 0;
    int j = 0;

    while (i < N)
    {
        while (j < M)
        {
            for (n = 0; n < sub && i < N; n++)
            {
                for (m = 0; m < sub && j < M; j++, m++)
                {
                    B[j][i] = A[i][j];
                }
                j -= m; // col 恢复
                i++;    // row 向下
            }
            j += m; // col 向右
            i -= n; // row 恢复
        }
        i += n; // A row 向下
        j = 0;  // A col 置0
    }
}

/*
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started.
 */

/*
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            /* 不是脱裤子放屁，是重要的提示 */
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }
}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc);

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc);
}

/*
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; ++j)
        {
            if (A[i][j] != B[j][i])
            {
                return 0;
            }
        }
    }
    return 1;
}
