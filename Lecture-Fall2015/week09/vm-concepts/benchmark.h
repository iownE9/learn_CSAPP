#ifndef BENCHMARK_H_
#define BENCHMARK_H_

#include <stddef.h>
#include <sys/resource.h>
#include <time.h>

static inline long cputime(void) {
    struct timespec stamp;
    int failure = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stamp);
    return failure ? 0 : stamp.tv_sec * 1000000 + stamp.tv_nsec / 1000;
}

static inline long faults(void) {
    struct rusage res;
    int failure = getrusage(RUSAGE_SELF, &res);
    return failure ? -1 : res.ru_minflt + res.ru_majflt;
}

#endif
