#include <stdio.h>
#include <sys/mman.h>

#define LENGTH 8192

int main(void)
{
    char *array = mmap((void *)0x7fffe0000000, LENGTH, PROT_READ | PROT_WRITE,
                       MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (array == MAP_FAILED)
    {
        perror("mmap");
        return 1;
    }

    // FIXME: I think there's a bug somewhere on the following line!
    // for (int index = 0; index <= LENGTH; ++index)
    for (int index = 0; index < LENGTH; ++index)
        array[index] = (char)('a' + index % 26);

    munmap(array, LENGTH);
    return 0;
}
