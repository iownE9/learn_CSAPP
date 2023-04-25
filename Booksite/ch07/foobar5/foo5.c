/*
    foo5.c
    p473
    gcc -Wall -Og -o foobar5 foo5.c bar5.c
*/
#include <stdio.h>
void f(void);

int y = 15212;
int x = 15213;

int main()
{
    f();
    printf("x = 0x%x y = 0x%x \n", x, y);
    return 0;
}

/*
gcc (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0

steve@Steve ~/l/B/c/foobar5 (main) [1]> gcc -Wall -Og -o foobar5 foo5.c bar5.c
/usr/bin/ld: /tmp/ccTwVxNT.o:(.bss+0x0): multiple definition of `x';
/tmp/ccttjlUx.o:(.data+0x0): first defined here
collect2: error: ld returned 1 exit status


.bss        Uninitialized static variables,
and global or static variables that are initialized to zero

.data       Initialized global and static C variables
*/