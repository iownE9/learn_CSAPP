/**
 * @author Steve
 * @date 2022/11/13
 * referenceURL: zh-cn 198
 * *
 * Compilation: gcc -Og main.c -o main.out
 * Compilation: gcc -Og -S main.c
 * *
 * Compilation: gcc -O1 -S main.c -o main_O1.s
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