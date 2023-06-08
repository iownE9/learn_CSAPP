/**
 * Compilation: gcc mm-test.c -o mm-test
 * Execution:   ./mm-test
 * *
 * Recombination:   gcc mm-test.c -o mm-test ; ./mm-test ; rm ./mm-test
 * *
 * description:
 **/

#include <stdio.h>
#include <stdlib.h>

/* 获取free块信息 */
#define GET_PREV(p) (*(unsigned long *)(p))
#define GET_NEXT(p) (*((unsigned long *)(p) + 1))
#define PUT_PREV(p, val) ((GET_PREV(p)) = ((unsigned long)(val)))
#define PUT_NEXT(p, val) ((GET_NEXT(p)) = ((unsigned long)(val)))

#define GET(p) (*(unsigned int *)(p))

int main(void)
{
    unsigned long *a = malloc(5 * sizeof(unsigned long));
    printf("addr a: %p\n", a);

    // 200000001
    a[0] = 1;
    // a[1] = a;
    PUT_NEXT(a, a);
    a[2] = 4;
    printf("%lx\n", GET_PREV(a));
    printf("%lx\n", GET_NEXT(a));
    printf("%lx\n", GET_PREV(GET_NEXT(a)));
    return 0;
}