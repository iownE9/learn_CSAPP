/**
 * referenceURL: zh-cn 195
 * *
 * Compilation: gcc -Og -S echo.c
 * Compilation: gcc -Og -fno-stack-protector -S echo.c -o echo_nsp.s
 * *
 * Compilation: gcc -O1 -S echo.c -o echo_O1.s
 * *
 * description:
 **/
#include <stdio.h>
#include <stddef.h>

/* Implementation of library function gets() Bug */
char *gets(char *s)
{
    int c;
    char *dest = s;

    while ((c = getchar()) != '\n' && c != EOF)
        *dest++ = c;

    if (c == EOF && dest == s)
        /* No characters read */
        return NULL;

    *dest++ = '\0'; /* Terminate string */
    return s;
}

/* Read input line and write it back */
void echo()
{
    char buf[8]; /* Way too small! */
    gets(buf);
    puts(buf);
}