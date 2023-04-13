/**
 * referenceURL: 配套习题
 * *
 * Compilation: gcc -Og -S get_line.c
 * Compilation: gcc -Og -c get_line.c
 * Compilation: objdump -d get_line.o > get_line.d
 * *
 * Compilation: gcc -O1 -S get_line.c -o get_line_O1.s
 * *
 * description:
 **/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/* This is very low-quality code.
It is intended to illustrate bad programming practices.
See Practice Problem 3.46. */

char *get_line()
{
    char buf[4];
    char *result;
    gets(buf);
    result = malloc(strlen(buf));
    strcpy(result, buf);
    return result;
}

char *get_line2()
{
    char buf[4];
    char *result;
    // fgets(buf, 4, stdin);
    gets(buf);

    result = malloc(strlen(buf) + 1);

    if (result)
    {
        strncpy(result, buf, 4);
    }

    return result;
}