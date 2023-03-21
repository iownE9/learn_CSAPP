/**
 * linux> gcc array_access.c -o array_access
 * linux> ./array_access
 * result: 9
 * description: Lecture-Fall2020-08  27
 **/

#include <stdio.h>

#define ZLEN 5
#define PCOUNT 4

typedef int zip_dig[ZLEN];

int main(int argc, char **argv)
{
    zip_dig pgh[PCOUNT] =
        {{1, 5, 2, 0, 6},
         {1, 5, 2, 1, 3},
         {1, 5, 2, 1, 7},
         {1, 5, 2, 2, 1}};
    int *linear_zip = (int *)pgh;
    int *zip2 = (int *)pgh[2];
    int result =
        pgh[0][0] +
        linear_zip[7] +
        *(linear_zip + 8) +
        zip2[1];
    printf("result: %d\n", result);
    return 0;
}