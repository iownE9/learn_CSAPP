/*
    foo3.c
    p472 一强一弱
    gcc -o foobar3 foo3.c bar3.c
*/
#include <stdio.h>
void f(void);

int x = 15213; // 强符合

int main()
{
    f();
    printf("x = %d\n", x);
    return 0;
}

/*
gcc (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0

steve@Steve ~/l/B/c/foobar3 (main) [1]> gcc -o foobar3 foo3.c bar3.c
/usr/bin/ld: /tmp/cccWvLte.o:(.bss+0x0): multiple definition of `x';
/tmp/ccLFgIQo.o:(.data+0x0): first defined here
collect2: error: ld returned 1 exit status

.bss        Uninitialized static variables,
and global or static variables that are initialized to zero

.data       Initialized global and static C variables
*/