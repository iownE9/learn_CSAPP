/**
 * *
 * Environment: Linux
 * Compilation: gcc 01-MemoryReferenceBug.c -o 01-MemoryReferenceBug
 * Execution:   ./01-MemoryReferenceBug
 * *
 * description: a[2] a[3] 会改变 d 的值
 **/

#include <stdio.h>

typedef struct
{
    int a[2];
    double d;
} struct_t;

double fun(int i)
{
    volatile struct_t s;
    s.d = 3.14;
    // Possibly out of bounds
    s.a[i] = 1073741824;
    // s.a[i] = 33;
    // s.a[i] = 10;
    return s.d;
}

int main(void)
{
    for (int i = 0; i < 7; i++)
    {
        printf("%d  %f\n\n", i, fun(i));
    }

    return 0;
}

/*
steve@D /a/l/lecture [SIGABRT]> gcc 01-MemoryReferenceBug.c -o 01-MemoryReferenceBug
steve@D /a/l/lecture> ./01-MemoryReferenceBug

0  3.140000

1  3.140000

2  3.140000

3  2.000001

4  3.140000

5  3.140000

*** stack smashing detected ***: terminated
fish: Job 1, './lect01_MemoryReferenceBug' terminated by signal SIGABRT (Abort)
steve@D /a/l/lecture [SIGABRT]>

*/