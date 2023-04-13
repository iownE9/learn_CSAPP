/**
 * referenceURL: zh-cn 148
 * *
 * Environment: Linux
 * Compilation: gcc -Og -S cread.c
 * Compilation: gcc -O1 -S -fno-if-conversion cread.c
 * *
 * Compilation: gcc -O1 -S cread.c -o cread_O1.s
 * *
 * description: 可以看到如今的编译器优化了这个bug
 **/

long cread(long *xp)
{
    return (xp ? *xp : 0);
}
