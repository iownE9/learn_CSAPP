/**
 * referenceURL: 配套习题
 * *
 * Environment: Linux
 * Compilation: gcc -Og -c goto_cond.c
 * Compilation: gcc -Og -S goto_cond.c
 * Compilation: objdump -d goto_cond.o > goto_cond.d
 * *
 * description:
 **/
void goto_cond(long a, long *p)
{
    if (p == 0)
        goto done;
    if (*p >= a)
        goto done;
    *p = a;
done:
    return;
}