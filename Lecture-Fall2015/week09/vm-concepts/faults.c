#include "benchmark.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

#define BYTES 102400

static long fill_twice(uint8_t *block, size_t size)
{
    long pfs, loop, total = 0;

    pfs = faults();
    for (size_t byte = 0; byte < size; ++byte)
        block[byte] = (uint8_t)(byte & 0xFFu);
    loop = faults() - pfs;
    total += loop;
    printf("\tloop 1: %2ld page faults\n", loop);

    pfs = faults();
    for (size_t byte = 0; byte < size; ++byte)
        block[byte] = (uint8_t) ~(byte & 0xFFu);
    loop = faults() - pfs;
    total += loop;
    printf("\tloop 2: %2ld page faults\n", loop);

    return total;
}

int main(void)
{
    long call, loops, pfs;
    uint8_t *one, *two;

    puts("calloc():");
    pfs = faults();
    one = calloc(1, BYTES);
    call = faults() - pfs;
    printf("\tcall:   %2ld page faults\n", call);
    loops = 0;
    if (one)
    {
        loops = fill_twice(one, BYTES);
        free(one);
    }
    printf("\tsum:    %2ld page faults\n\n", call + loops);

    puts("mmap():");
    pfs = faults();
    two = mmap(NULL, BYTES, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS,
               -1, 0);
    call = faults() - pfs;
    printf("\tcall:   %2ld page faults\n", call);
    loops = 0;
    if (two != MAP_FAILED)
    {
        loops = fill_twice(two, BYTES);
        munmap(two, BYTES);
    }
    printf("\tsum:    %2ld page faults\n", call + loops);

    return 0;
}
