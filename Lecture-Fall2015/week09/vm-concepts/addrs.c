#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

const char rodata[] = "rodata";
char data[] = "data";
char bss[1];
extern int main(void);

static void print_addrs(const char *heap) {
    char stack[] = "stack";
    printf("\ttext:   %#lx\n", (uintptr_t)main);
    printf("\trodata: %#lx\n", (uintptr_t)rodata);
    printf("\tdata:   %#lx\n", (uintptr_t)data);
    printf("\tbss:    %#lx\n", (uintptr_t)bss);
    printf("\theap:   %#lx\n", (uintptr_t)heap);
    printf("\tstack:  %#lx\n", (uintptr_t)stack);
}

int main(void) {
    char *heap = malloc(1);
    if (!heap) {
        perror("failed to malloc() memory");
        return 1;
    }

    puts("Parent:");
    print_addrs(heap);
    fflush(stdout);

    pid_t child = fork();
    if (child == -1) {
        perror("fork");
        return 1;

    } else if (child == 0) {
        // Child side of the fork.
        puts("Child:");
        print_addrs(heap);
        free(heap);
        return 0;

    } else {
        // Parent side of the fork.
        // Wait for the child to finish printing.
        int status;
        if (waitpid(child, &status, 0) != child) {
            perror("waitpid");
            return 1;
        } else if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
            // This shouldn't happen, so we don't bother decoding the
            // status in detail.
            fprintf(stderr, "Child exited unsuccessfully (code %04x)\n",
                    status);
            return 1;
        }

        free(heap);
        return 0;
    }
}
