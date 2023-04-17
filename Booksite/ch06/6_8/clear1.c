//  description: zh-cn p420

#define N 1000

typedef struct
{
    int vel[3];
    int acc[3];
} point;

point p[N];

void clear1(point *p, int n)
{
    int i, j;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < 3; j++)
            p[i].vel[j] = 0;
        for (j = 0; j < 3; j++)
            p[i].acc[j] = 0;
    }
}