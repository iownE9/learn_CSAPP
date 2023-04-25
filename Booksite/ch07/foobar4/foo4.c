/*
    foo4.c
    p473 两弱
    gcc -o foobar4 foo4.c bar4.c
*/
#include <stdio.h>
void f(void);
int x;
int main()
{
    x = 15213;
    f();
    printf("x = %d\n", x);
    return 0;
}

/*
gcc (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0

steve@Steve ~/l/B/c/foobar4 (main)> gcc -o foobar4 foo4.c bar4.c
/usr/bin/ld: /tmp/ccnuRftp.o:(.bss+0x0): multiple definition of `x'; 
/tmp/ccndAsLG.o:(.bss+0x0): first defined here
collect2: error: ld returned 1 exit status

.bss        Uninitialized static variables,
and global or static variables that are initialized to zero

.data       Initialized global and static C variables
*/