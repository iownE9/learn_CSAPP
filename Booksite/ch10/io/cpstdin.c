/* $begin cpstdin */
#include "csapp.h"

// >strace ./cpstdin
// strace -e trace=write ./cpstdin
// strace -e trace=write,read ./cpstdin

int main(void)
{
    char c;

    while (Read(STDIN_FILENO, &c, 1) != 0)
        Write(STDOUT_FILENO, &c, 1);

    exit(0);
}
/* $end cpstdin */
