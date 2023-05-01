#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <math.h>
#include <unistd.h>

int main(int argc, char *argv[])
{

    /*
     * What does char *otparg represent? What about int
     * optind, int opterr, and int optopt?
     * Reference the man page or ask for help if you are struggling
     * with reading the man page.
     *
     * clang -Wall -Werror -lm  pyth_solver.c   -o pyth_solver
     *
     */
    extern char *optarg;
    extern int optind, opterr, optopt;

    int errorFlag = (argc == 4 || argc == 3);

    // what is arg?
    char arg;

    // declaring verbose mode, a, b, c
    int verbose = 0;
    float a = -1;
    float b = -1;
    float c = -1;
    char *optstring = "va:b:c:";

    // collecting arguments
    while ((arg = getopt(argc, argv, optstring)) != -1)
    {
        switch (arg)
        {
        case 'v':
            verbose = 1;
            break;
        case 'a':
            a = atof(optarg);
            break;
        case 'b':
            b = atof(optarg);
            break;
        case 'c':
            c = atof(optarg);
            break;
        default:
            errorFlag = 1;
            break;
        }
    }

    if (errorFlag || a <= 0 || b <= 0 || c <= 0)
    {
        printf("Error: invalid arguments\n");
        exit(errorFlag);
    }
    else if (a != -1 && b != -1 && c != -1)
    {
        int match = (c == sqrt(a * a + b * b));
        if (verbose)
        {
            printf("a^2 = %f\n", a * a);
            printf("b^2 = %f\n", b * b);
            printf("c^2 = %f\n", c * c);
        }
        printf("Those values %s work\n", match ? "do" : "don't");
    }

    return 0;
}