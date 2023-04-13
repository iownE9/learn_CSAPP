/**
 * referenceURL: zh-cn 198
 * *
 * Compilation: gcc -Og -S main.c
 * *
 * Compilation: gcc -O1 -S main.c -o main_O1.s
 * *
 * Compilation: gcc main.c -o main
 * Execution:   ./main
 * *
 * description:
 **/

#include <stdio.h>

int main()
{
    long local;
    printf("local at %p\n", &local);

    return 0;
}