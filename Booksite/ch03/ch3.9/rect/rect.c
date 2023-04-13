/**
 * referenceURL: zh-cn 183
 * *
 * description:
 **/

#include <stdio.h>

struct rect
{
    long llx;             /* X coordinate of lower-left corner */
    long lly;             /* Y coordinate of lower-left corner */
    unsigned long width;  /* Width (in pixels) */
    unsigned long height; /* Height (in pixels) */
    unsigned color;       /* Coding of color */
};

long area(struct rect *rp)
{
    return (*rp).width * (*rp).height;
}

void rotate_left(struct rect *rp)
{
    /* Exchange width and height */
    long t = rp->height;
    rp->height = rp->width;
    rp->width = t;
    /* Shift to new lower-left corner */
    rp->llx -= t;
}

int main(void)
{
    struct rect r;
    r.llx = r.lly = 0;
    r.color = 0xFF00FF;
    r.width = 10;
    r.height = 20;

    struct rect r2 = {0, 0, 0xFF00FF, 10, 20};
    return 0;
}