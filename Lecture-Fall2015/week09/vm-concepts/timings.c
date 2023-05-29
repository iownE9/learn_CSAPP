#include "benchmark.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

#define BYTES 102400

static long fill_twice(uint8_t *block, size_t size)
{
    long ts, loop, total = 0;

    ts = cputime();
    for (size_t byte = 0; byte < size; ++byte)
        block[byte] = (uint8_t)(byte & 0xFFu);
    loop = cputime() - ts;
    total += loop;
    printf("\tloop 1: %3ld microseconds\n", loop);

    ts = cputime();
    for (size_t byte = 0; byte < size; ++byte)
        block[byte] = (uint8_t) ~(byte & 0xFFu);
    loop = cputime() - ts;
    total += loop;
    printf("\tloop 2: %3ld microseconds\n", loop);

    return total;
}

int main(void)
{
    long call, loops, ts;
    uint8_t *one, *two;

    puts("calloc():");
    ts = cputime();
    one = calloc(1, BYTES);
    call = cputime() - ts;
    printf("\tcall:   %3ld microseconds\n", call);
    loops = 0;
    if (one)
    {
        loops = fill_twice(one, BYTES);
        free(one);
    }
    printf("\tsum:    %3ld microseconds\n\n", call + loops);

    puts("mmap():");
    ts = cputime();
    two = mmap(NULL, BYTES, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS,
               -1, 0);
    call = cputime() - ts;
    printf("\tcall:   %3ld microseconds\n", call);
    loops = 0;
    if (two != MAP_FAILED)
    {
        loops = fill_twice(two, BYTES);
        munmap(two, BYTES);
    }
    printf("\tsum:    %3ld microseconds\n", call + loops);

    return 0;
}
