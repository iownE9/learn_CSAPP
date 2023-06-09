#include "int_fn_ptrs.h"

void print_int(elem e)
{
    REQUIRES(e != NULL);
    int val = *(int *)(e);
    printf("%d ", val);
}

bool ints_equal(elem e1, elem e2)
{
    REQUIRES(e1 != NULL && e2 != NULL);
    /* TODO: Implement this */
    return *(int *)(e1) == *(int *)(e2);
}

void add_1(elem e)
{
    REQUIRES(e != NULL);
    int val = *(int *)(e);
    *(int *)(e) = val + 1;
}

void square(elem e)
{
    REQUIRES(e != NULL);
    int val = *(int *)e;
    *(int *)(e) = val * val;
}

void next_pow_2(elem e)
{
    REQUIRES(e != NULL);
    /* TODO: Implement this */
    int val = *(int *)(e);
    int msb = 0;
    for (int i = sizeof(int) * 8 - 1; i >= 0; i--){
        if ((val >> i) & 0x1){
            msb = i + 1;
            break;
        }
    }
    *(int *)(e) = (1 << msb);
}
