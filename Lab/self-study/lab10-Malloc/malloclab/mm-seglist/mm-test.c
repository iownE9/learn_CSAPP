/**
 * Compilation: gcc mm-test.c -o mm-test -lm
 * Execution:   ./mm-test
 * *
 * Recombination:   gcc mm-test.c -o mm-test ; ./mm-test ; rm ./mm-test
 * *
 * description:
 **/
#include <math.h> /* 添加 */

#include <stdio.h>
#include <stdlib.h>
#define SEGNUM 9 /* 九类 */
#define OFFSET 4 /* 索引偏移 */
/* 获取free块信息 */
#define N_IDX(size) (((int)(log(size) / log(2))) - OFFSET)
#define MAX(x) (((x) < (SEGNUM)) ? (x) : (SEGNUM - 1))
#define GET_N(size) (MAX(N_IDX(size)))

#define GET_SEGLIST(n) (((unsigned long *)free_listp) + (2 * n))
int main(void)
{

    printf("%d\n", GET_N(24));
    printf("%d\n", GET_N(32));
    printf("%d\n", GET_N(64));
    printf("%d\n", GET_N(66));
    printf("%d\n", GET_N(128));
    printf("%d\n", GET_N(145));
    printf("%d\n", GET_N(4096));
    printf("%d\n", GET_N(4096 * 3));
    printf("%d\n", GET_N(1788226));

    return 0;
}