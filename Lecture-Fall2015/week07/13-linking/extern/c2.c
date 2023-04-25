#include <stdio.h>
#include "global.h"

int g = 1;
int main(int argc, char argv[])
{
    int t = f();
    printf("Calling f yields %d\n", t);
    // Calling f yields 2
    return 0;
}
