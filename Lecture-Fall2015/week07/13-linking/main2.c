/*
    main2.c

生成静态库 libvector.a
linux> gcc -c addvec.c multvec.c
linux> ar rcs libvector.a addvec.o multvec.o

链接静态库 libvector.a
linux> gcc -c main2.c
linux> gcc -static -o prog2c main2.o ./libvector.a
or equivalently,
linux> gcc -c main2.c
linux> gcc -static -o prog2c main2.o -L. -lvector

动态链接
linux> gcc -shared -fpic -o libvector.so addvec.c multvec.c
linux> gcc -o prog2l main2.c ./libvector.so

*/
/* $begin main2 */
#include <stdio.h>
#include "vector.h"

int x[2] = {1, 2};
int y[2] = {3, 4};
int z[2];

int main()
{
    addvec(x, y, z, 2);
    printf("z = [%d %d]\n", z[0], z[1]);
    return 0;
}
/* $end main2 */
