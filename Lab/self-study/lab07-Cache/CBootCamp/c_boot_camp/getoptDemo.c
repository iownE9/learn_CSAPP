/**
 * referenceURL: http://t.csdn.cn/jI399
 * *
 * Compilation: gcc -g getoptDemo.c -o getoptDemo
 * Execution:   ./getoptDemo -x 2
 * *
 * description:
 **/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

int main(int argc, char **argv)
{
    int opt, x;
    /* looping over arguments */
    while (-1 != (opt = getopt(argc, argv, "x:")))
    {
        switch (opt)
        {
        case 'x':
            x = atoi(optarg);
            printf("x: %d\n", x);
            break;
        default:
            printf("wrong argument\n");
            break;
        }
    }
}
