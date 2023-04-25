// Lecture-Fall2020/14-Linking.pdf-20
// gcc -Wall -Og -o mismatch mismatch-main.c mismatch-variable.c

#include <stdio.h>

long int x; /* Weak symbol */
int main(int argc,
         char *argv[])
{
    printf("%ld\n", x);
    return 0;
}

/*

steve@Steve ~/l/L/w/1/mismatch (main)> gcc -Wall -Og -o mismatch mismatch-main.c mismatch-variable.c
/usr/bin/ld: /tmp/cczP9Z9s.o:(.data+0x0): multiple definition of `x';
/tmp/cchT6Uk4.o:(.bss+0x0): first defined here
collect2: error: ld returned 1 exit status

*/