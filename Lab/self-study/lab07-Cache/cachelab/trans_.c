#include <stdlib.h>
#include <stdio.h>

// gcc trans_.c -o trans_
// ./trans_ M N

void transpose_submit(int M, int N) //  int A[N][M], int B[M][N])
{
    int sub = 8;
    int m = 0;
    int n = 0;
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
                    // A 的轨迹
                    printf("%d %d -> ", i, j);
                }
                printf("\n");
                j -= m; // col 恢复
                i++;    // row 向下
            }
            printf("======\n");

            j += m; // col 向右
            i -= n; // row 恢复
        }
        i += n; // A row向下
        j = 0;  // A col置0
    }
}

int main(int argc, char **argv)
{
    int N = atoi(argv[1]);
    int M = atoi(argv[2]);
    printf(" N=%d  M=%d\n", N, M);

    transpose_submit(M, N);
}