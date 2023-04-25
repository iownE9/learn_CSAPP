/* main.c */

// gcc -Og -o prog main.c sum.c

/* $begin main */
int sum(int *a, int n);

int array[2] = {1, 2};

int main()
{
    int val = sum(array, 2);
    return val;
}
/* $end main */
