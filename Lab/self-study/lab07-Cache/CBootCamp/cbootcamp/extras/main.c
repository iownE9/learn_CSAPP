/*
	@file Main.c
	@brief This file has a few test cases to verify your program.
		   Feel free to add more test cases for individual functions
	@date <Fill this In>
	@author Hanlei
*/

#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** @brief Represents the size of the data we are testing the queue with**/
#define SIZE (sizeof(int))

int main()
{
	// Node 1
	boundary *queue = init_queue();
	printf("Testing Enqueue ...\n");
	char *id = "A";
	int *data = malloc(SIZE);
	*data = 15213;
	printf("Inserting the following element into queue: %d\n", *data);
	enqueue(queue, id, data, SIZE);
	node *check_node = find_object(queue, id);
	printf("Verifying element in queue:");
	if (check_node != NULL)
		printf("PASS\n");
	else
	{
		printf("FAIL\n");
		free(data);
		exit(1);
	}
	printf("Verifying correct data: %d\n", (*(int *)(check_node->data)));

	// Node 2
	char *id2 = "B";
	int *data2 = malloc(SIZE);
	*data2 = 15122;

	printf("Inserting the following element into queue: %d\n", *data2);
	enqueue(queue, id2, data2, SIZE);
	check_node = find_object(queue, id2);
	printf("Verifying element in queue:");
	if (check_node != NULL)
		printf("PASS\n");
	else
	{
		printf("FAIL\n");
		free(data);
		free(data2);
		exit(1);
	}
	printf("Verifying correct data: %d\n", (*(int *)(check_node->data)));

	// Dequeue and verify queue behavior
	printf("Testing Dequeue ...\n");
	int *q_data = malloc(SIZE);
	dequeue(queue, q_data, SIZE);

	printf("Verifying correct data after dequeue:");
	if (*q_data == *data)
		printf("PASS\n");
	else
	{
		printf("FAIL: Expected(%d) Received(%d)\n", *data, *q_data);
		free(q_data);
		free(data);
		free(data2);
		exit(1);
	}
	check_node = find_object(queue, id);
	printf("Verifying element not in queue:");
	if (check_node == NULL)
		printf("PASS\n");
	else
	{
		printf("FAIL\n");
		free(q_data);
		free(data);
		free(data2);
		exit(1);
	}

	dequeue(queue, q_data, SIZE);
	printf("Verifying correct data after dequeue:");

	if (*q_data == *data2)
		printf("PASS\n");
	else
	{
		printf("FAIL: Expected(%d) Received(%d)\n", *data2, *q_data);
		free(q_data);
		free(data);
		free(data2);
		exit(1);
	}
	check_node = find_object(queue, id);
	printf("Verifying element not in queue:");
	free(q_data);
	free(data);
	free(data2);
	if (check_node == NULL)
		printf("PASS\n");
	else
	{
		printf("FAIL\n");
		exit(1);
	}
}

/*
添加:
free(q_data);
free(data);
free(data2);

==5788== HEAP SUMMARY:
==5788==     in use at exit: 32 bytes in 2 blocks
==5788==   total heap usage: 12 allocs, 10 frees, 1,160 bytes allocated
==5788==
==5788== 32 (16 direct, 16 indirect) bytes in 1 blocks are definitely lost in loss record 2 of 2
==5788==    at 0x4E050C5: malloc (vg_replace_malloc.c:393)
==5788==    by 0x10925E: init_queue (ref-queue.c:24)
==5788==    by 0x109574: main (main.c:20)
==5788==
==5788== LEAK SUMMARY:
==5788==    definitely lost: 16 bytes in 1 blocks
==5788==    indirectly lost: 16 bytes in 1 blocks
==5788==      possibly lost: 0 bytes in 0 blocks
==5788==    still reachable: 0 bytes in 0 blocks
==5788==         suppressed: 0 bytes in 0 blocks
==5788==
==5788== For lists of detected and suppressed errors, rerun with: -s
==5788== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)

剩余的 1 errors 应该是 free(boundary)
client should free memory allocated by client code
library should free memory allocated by library code
故不在main.c中修改

*/