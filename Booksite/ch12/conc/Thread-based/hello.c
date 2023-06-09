/*
 * hello.c - Pthreads "hello, world" program
 * p692
 */
/* $begin hello */
#include "csapp.h"

void *thread(void *vargp); // line:conc:hello:prototype

// line:conc:hello:main
int main()
{
    pthread_t tid;                            // line:conc:hello:tid
    Pthread_create(&tid, NULL, thread, NULL); // line:conc:hello:create
    Pthread_join(tid, NULL);                  // line:conc:hello:join
    exit(0);                                  // line:conc:hello:exit
}

// line:conc:hello:beginthread
void *thread(void *vargp) /* thread routine */
{
    printf("Hello, world!\n");
    return NULL; // line:conc:hello:return
} 
// line:conc:hello:endthread
/* $end hello */
