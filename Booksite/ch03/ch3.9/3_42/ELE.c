/**
 * referenceURL: 配套习题
 * *
 * Compilation: gcc -Og -S ELE.c
 * *
 * Compilation: gcc -O1 -S ELE.c -o ELE_O1.s
 * *
 * description:
 **/

struct ELE
{
    long v;
    struct ELE *p;
};

long fun(struct ELE *ptr)
{
    long val = 0;
    while (ptr)
    {
        val *= ptr->v;
        ptr = ptr->p;
    }
    return val;
}