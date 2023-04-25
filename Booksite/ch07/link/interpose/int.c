/*
 * hello.c - Example program to demonstrate different ways to
 *           interpose on the malloc and free functions.
 *
 * Note: be sure to compile unoptimized (-O0) so that gcc won't
 * optimize away the calls to malloc and free.
 */
/* $begin interposemain */
#include <stdio.h>
#include <malloc.h>

int main()
{
    int *p = malloc(32);
    free(p);
    return (0);
}
/* $end interposemain */

/*
Lecture-Fall2015\week07\13-linking\interpose

参数 -Dxxx 对应 mymalloc.h 的 #ifdef xxx

1. 编译时打桩

linux> gcc -DCOMPILETIME -c mymalloc.c
linux> gcc -I. -o intc int.c mymalloc.o
linux> ./intc
malloc(32)=0x55f2d111e2a0
free(0x55f2d111e2a0)


2. 链接时打桩

linux> gcc -DLINKTIME -c mymalloc.c
linux> gcc -c int.c
linux> gcc -Wl,--wrap,malloc -Wl,--wrap,free -o intl int.o mymalloc.o
linux> ./intl
malloc(32) = 0x55e511e132a0
free(0x55e511e132a0)

3. 运行时打桩

linux> gcc -DRUNTIME -shared -fpic -o mymalloc.so mymalloc.c -ldl
linux> gcc -o intr int.c
linux> LD_PRELOAD="./mymalloc.so" ./intr

# bash shell
linux> (setenv LD_PRELOAD "./mymalloc.so"; ./intr; unsetenv LD_PRELOAD)

*/