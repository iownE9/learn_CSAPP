#include "csapp.h"

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define numStudents 1521300

void *reader();
void *writer();

/* Making the program faster
  requires changing only the
  way we lay out the data

    make falseSharing
  没看懂,要干啥的 :) */
struct student
{
    int studentScore;
    int studentID;
};

struct student students[numStudents];
int scoreSum = 0;

int main()
{

    struct timeval start, end;
    gettimeofday(&start, NULL);

    pthread_t tid_reader;
    pthread_t tid_writer;

    Pthread_create(&tid_writer, NULL, writer, NULL);
    Pthread_create(&tid_reader, NULL, reader, NULL);

    Pthread_join(tid_writer, NULL);
    Pthread_join(tid_reader, NULL);

    gettimeofday(&end, NULL);
    long seconds = (end.tv_sec - start.tv_sec);
    long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
    printf("%ld seconds and %ld microseconds\n", seconds, micros);

    return 0;
}

void *reader()
{
    for (int i = 0; i < numStudents; i++)
        scoreSum += students[i].studentScore;

    return NULL;
}

void *writer()
{
    for (int i = 0; i < numStudents; i++)
        students[i].studentID = i;

    return NULL;
}
