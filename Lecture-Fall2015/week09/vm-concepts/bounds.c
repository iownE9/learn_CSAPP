#include "benchmark.h"

#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>

#define BYTES (16 * 1024)

int main(void)
{
    uint8_t *rgn = mmap(NULL, BYTES, PROT_READ | PROT_WRITE,
                        MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (rgn == MAP_FAILED)
    {
        perror("mmap");
        return 1;
    }

    for (size_t byte = 0; byte < BYTES; ++byte)
    {
        long pfs = faults();
        rgn[byte] = (uint8_t)byte;
        if (faults() != pfs)
            // 4K
            printf("Page fault at offset 0x%05lx (%5lu)\n", byte, byte);
    }

    munmap(rgn, BYTES);
    return 0;
}
