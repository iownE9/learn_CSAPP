#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

struct person_node
{
    char *name;
    int age;
};

struct pet_node
{
    char *name;
    char type[10];
};

typedef struct person_node person;
typedef struct pet_node pet;
// 这一行跟 sol 的还不一样 艹

int main()
{
    /* TODO: dynamically allocate enough memory, assign the blocks to these pointers */

    int *A; // Construct a 10-elmeent integer array
    A = malloc(sizeof(int) * 10);

    free(A);

    int **B; // Construct a 2D array of 10 x 10 integers,
    B = malloc(sizeof(int *) * 10);
    for (int i = 0; i < 10; i++)
        B[i] = malloc(sizeof(int) * 10);

    for (int i = 0; i < 10; i++)
        free(B[i]);
    free(B);

    person *C; // Construct an array of 10 persons, allocate 10 characters for each name
    C = malloc(sizeof(person) * 10);
    for (int i = 0; i < 10; i++)
        C[i].name = malloc(sizeof(char) * 10);

    for (int i = 0; i < 10; i++)
        free(C[i].name);
    free(C);

    pet *D; // Construct an array of 10 pets, allocate 10 characters for each name;
    D = malloc(sizeof(pet) * 10);
    // type[10] 已被 sizeof(pet) 包含

    for (int i = 0; i < 10; i++)
        D[i].name = malloc(sizeof(char) * 10);

    for (int i = 0; i < 10; i++)
        free(D[i].name);
    free(D);
    // free any memory you just allocated before you return!
    return 0;
}
