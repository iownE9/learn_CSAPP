/**
 * referenceURL: 配套习题
 * *
 * Environment: Linux
 * Compilation: gcc -Og -S sum_element.c
 * *
 * Compilation: gcc -O1 -S sum_element.c -o sum_element_O1.s
 * *
 * description:
 **/

#define M 5
#define N 7

long P[M][N];
long Q[N][M];

long sum_element(long i, long j)
{
    return P[i][j] + Q[j][i];
}