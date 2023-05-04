#define _XOPEN_SOURCE 700
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

static inline unsigned long timestamp(void)
{
    struct timespec tv;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tv);
    return tv.tv_sec * 1000000 + tv.tv_nsec / 1000;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "usage: %s byte-count\n", argv[0]);
        return 1;
    }

    errno = 0;
    char *endp;
    unsigned long nbytes = strtoul(argv[1], &endp, 10);
    if (endp == argv[1] || *endp != '\0' || errno || nbytes == 0)
    {
        fprintf(stderr, "invalid byte-count argument '%s'\n", argv[1]);
        return 1;
    }

    char c = '\n';
    unsigned long start_time, end_time;

    printf("Writing %lu byte%s (one at a time) with fputc()...",
           nbytes, nbytes > 1 ? "s" : "");
    start_time = timestamp();

    FILE *stream = fopen("/dev/null", "w");
    if (!stream)
    {
        perror("/dev/null");
        return 1;
    }

    // _IOLBF 遇换行符
    // _IOFBF 全缓冲 大小 0
    setvbuf(stream, NULL, _IOFBF, 0); // Buffer in large chunks.

    for (unsigned long i = 0; i < nbytes; i++)
    {
        // 向 stream 写入 c
        fputc(c, stream);
    }
    if (fclose(stream))
    {
        perror("/dev/null: write error");
        return 1;
    }

    end_time = timestamp();
    printf("%lu microseconds\n", (end_time - start_time));

    printf("Writing %lu byte%s (one at a time) with write()...",
           nbytes, nbytes > 1 ? "s" : "");
    start_time = timestamp();

    int fd = open("/dev/null", O_WRONLY);
    if (fd < 0)
    {
        perror("/dev/null");
        return 1;
    }
    for (unsigned long i = 0; i < nbytes; i++)
    {
        // 向 fd 写入 1 字符 c
        if (write(fd, &c, 1) < 1)
        {
            perror("write");
            return 1;
        }
    }
    if (close(fd) < 0)
    {
        perror("/dev/null: write error");
        return 1;
    }

    end_time = timestamp();
    printf("%lu microseconds\n", (end_time - start_time));

    return 0;
}
