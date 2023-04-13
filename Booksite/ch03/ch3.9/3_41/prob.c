/**
 * referenceURL: 配套习题
 * *
 * Environment: Linux
 * Compilation: gcc -Og -S prob.c
 * *
 * Compilation: gcc -O1 -S prob.c -o prob_O1.s
 * *
 * description:
 **/

struct prob
{
    int *p;
    struct
    {
        int x;
        int y;
    } s;
    struct prob *next;
};

void st_init(struct prob *sp)
{
    sp->s.x = sp->s.y;
    sp->p = &(sp->s.x);
    sp->next = sp;
}