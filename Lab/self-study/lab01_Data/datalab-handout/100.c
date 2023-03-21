/**
 * @author Steve
 * @date 2022/10/24
 * *
 * Environment: Linux
 * Compilation: gcc 100.c -o 100
 * Execution:   ./100
 * *
 * Recombination:   gcc 100.c -o 100 ; ./100 ; rm ./100
 * *
 * description:
 **/

#include <stdio.h>
#include <string.h>

int main(void)
{
    int T = 0, i = 0;
    double avg = 0.0;
    char a[255] = {0};
    scanf("%d", &T);
    getchar();
    for (i = 0; i < T; i++)
    {
        gets(a);
        // printf("%s", a);
        int len = strlen(a);
        int n = 0;
        for (int idx = 0; idx < len; idx += 2)
        {
            int temp = a[idx] - '0';
            // printf("temp=%d\n", temp);
            avg += temp;
            n++;
            // printf("%d\n", a[idx] - '0');
            // printf("avg=%1.f\n", avg);
        }

        printf("%.1f \n", 1.0 * avg / n);
    }

    return 0;
}