#include <stdlib.h>

struct rec
{
    int a[4];
    size_t i;
    struct rec *next;
};

void set_i(struct rec *r, size_t val)
{
    r->i = val;
}

int *get_ap(struct rec *r, size_t idx)
{
    return &r->a[idx];
}

// description: Lecture-Fall2020-08  33
long length(struct rec *r)
{
    long len = 0L;
    while (r)
    {
        len++;
        r = r->next;
    }
    return len;
}
// .L11:                   # loop:
//    addq $1, %rax        # len ++
//    movq 24(%rdi), %rdi  # r = Mem[r+24]
//    testq %rdi, %rdi     # Test r
//    jne .L11             # If != 0, goto loop

int check_val(struct rec *r, int val)
{
    int found = 0;
    while (!found && r)
    {
        size_t i = r->i;
        if (r->a[i] == val)
            found = 1;
        else
            r = r->next;
    }
    return found;
}

void set_val(struct rec *r, int val)
{
    while (r)
    {
        size_t i = r->i;
        // No bounds check
        r->a[i] = val;
        r = r->next;
    }
}
