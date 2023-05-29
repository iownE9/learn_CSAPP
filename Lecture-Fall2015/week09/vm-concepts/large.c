#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/sysinfo.h>
#include <time.h>
#include <unistd.h>

#define BYTES (1024 * 1024 * 1024) // 1 GB

typedef enum { TOUCH_NOT = 0, TOUCH_READ = 1, TOUCH_WRITE = 2 } touch_mode;

int main(int argc, char **argv) {
    touch_mode mode;

    if (argc <= 1) {
        mode = TOUCH_NOT;
    } else if (argc == 2 && !strcmp(argv[1], "read")) {
        mode = TOUCH_READ;
    } else if (argc == 2 && !strcmp(argv[1], "write")) {
        mode = TOUCH_WRITE;
    } else {
        fputs("usage: ./large [read|write]\n", stderr);
        return 1;
    }

    struct sysinfo inf;
    if (sysinfo(&inf)) {
        perror("sysinfo()");
        return 1;
    }
    long pagesize = sysconf(_SC_PAGESIZE);
    if (pagesize < 0) {
        perror("sysconf");
        return 1;
    }

    printf("System has %.2f GB of main memory and %.2f GB of swap\n",
           (double)inf.totalram * inf.mem_unit / BYTES,
           (double)inf.totalswap * inf.mem_unit / BYTES);

    time_t tick = time(NULL);
    for (int gigs = 0;; ++gigs) {
        unsigned char *p = mmap(0, BYTES, PROT_READ | PROT_WRITE,
                                MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        if (p == MAP_FAILED)
        {
            fprintf(stderr, "mmap failed after allocating %d GB: %s\n", gigs,
                    strerror(errno));
            return 1;
        }
        // ./large 运行时 只分配页表 惰性内存 p565
        // 逐个操作为了实现实际分配内存
        if (mode == TOUCH_READ) {
            for (long page = 0; page < BYTES; page += pagesize) {
                if (p[page] != 0) {
                    fprintf(stderr, "strange: %p[%ld] = %u\n", (void *)p, page,
                            p[page]);
                }
            }
        } else if (mode == TOUCH_WRITE) {
            for (long page = 0; page < BYTES; page += pagesize) {
                p[page] = 1;
            }
        }
        time_t tock = time(NULL);
        if (tock - tick > 0) {
            printf("Allocated%s %d GB\n",
                   (mode == TOUCH_NOT
                        ? ""
                        : (mode == TOUCH_READ ? " and read" : " and wrote")),
                   gigs);
            tick = tock;
        }
    }
    // not reached
}
