/**
 * @author Steve
 * @date 2022/10/30
 * referenceURL: 配套习题解答
 * *
 * Environment: Linux
 * Compilation: gcc 02-03-Byte_Representation.c -o 02-03-Byte_Representation
 * Execution:   ./02-03-Byte_Representation
 * *
 * Recombination:   gcc 02-03-Byte_Representation.c -o 02-03-Byte_Representation ; ./02-03-Byte_Representation ; rm ./02-03-Byte_Representation
 * *
 * description: pdf59
 **/

#include <stdio.h>

typedef unsigned char *pointer;

void show_bytes(pointer start, size_t len)
{
    size_t i;
    for (i = 0; i < len; i++)
        printf("%p\t0x%.2x\n", start + i, start[i]);
    printf("\n");
}

int main(void)
{
    int a = 15213;
    printf("int a = 15213;\n");
    show_bytes((pointer)&a, sizeof(int));
    int B = -15213;
    printf("int B = -15213;\n");
    show_bytes((pointer)&B, sizeof(int));
    return 0;
}
