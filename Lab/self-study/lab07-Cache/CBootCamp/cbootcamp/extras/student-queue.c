/*
	@file Student-Queue.c
	@brief This file maintains all the functions you will need to implement a generic queue
	@date <Fill this In>
	@author Hanlei
*/
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
	@brief Creates the initial queue by creating two encompassing blocks and initializing all the values
	@param none
	@return Pointer to the head of the queue
*/
boundary *init_queue(void)
{
	// TODO: Create Head and Tail Nodes and initialize all default values
	boundary *head = malloc(sizeof(boundary));
	boundary *tail = malloc(sizeof(boundary));

	head->other_bound = tail;
	tail->other_bound = head;

	head->queue_pointer = NULL;
	tail->queue_pointer = NULL;
	return head;
}

/*
	@brief Finds the requested data inside the queue using linear search
	@param head - Start of Queue
	@param id - id of data you are looking for
	@return Pointer to object containing data if found, NULL otherwise
*/
node *find_object(boundary *head, char *id)
{
	// head = head;
	// id = id;
	// TODO: Check any invariants and return NULL if failure
	if (head == NULL)
		return NULL;

	// TODO: Init queue rover
	node *temp = head->queue_pointer;
	// TODO: Linear Search through all nodes until end of cache to find ID
	while (temp != NULL)
	{
		if (strcmp(temp->id, id) == 0)
			return temp;
		temp = temp->next;
	}
	return NULL;
}

/*
	@brief Adds an element to the queue
	@param id - Character buffer containing the id
	@param data - pointer to generic data
	@param size - size of generic data
	@return Status Value - 0 for success, non-zero for error
*/
int enqueue(boundary *head, char *id, void *data, int size)
{
	// head = head;
	// id = id;
	// data = data;
	// size = size;
	// TODO: Check any invariants and return status code if failure
	if (head == NULL)
		return -1;
	// TODO: Create a new node and fill in relevant information
	// You can use built-in functions to copy data.
	// Hint: strcpy, memcpy, strlen
	node *new_node = malloc(sizeof(node));
	new_node->id = malloc(strlen(id) + 1);
	strcpy(new_node->id, id);
	new_node->data = malloc(size);
	new_node->len = size;
	memcpy(new_node->data, data, size);
	// TODO: Add individual entry to the queue
	// Hint: Are there any edge cases you need to worry about?
	if (head->queue_pointer != NULL)
		add_node(head, new_node);
	else
	{
		head->queue_pointer = new_node;
		head->other_bound->queue_pointer = new_node;
		new_node->next = NULL;
		new_node->prev = NULL;
	}

	// TODO: Are all the functions you used safe? Is there a better way to implement this?
	// Feel free to modify the function header to whatever you want to do it, if you have time.

	return 0;
}

/*
	@brief Removes element from the queue
	@param head - Pointer to start of queue
	@param return_data - buffer pre allocated by user that is large enough for data
	@param size - Amount of bytes that the user expects to be returned in buffer
	@return Status Value - 0 for success, non-zero for error
*/
int dequeue(boundary *head, void *return_data, int size)
{
	// head = head;
	// return_data = return_data;
	// size = size;
	// TODO: Check any invariants and return status code if failure
	node *return_node = head->queue_pointer;
	if (size < return_node->len)
		return -1;

	// TODO: Remove the node at the start of the queue and splice
	// together the rest of the nodes
	// Hint: Are there any edge cases you need to worry about?
	if (return_node->next != NULL)
	{
		head->queue_pointer = head->queue_pointer->next;
		return_node->next->prev = NULL;
	}
	else
	{
		head->queue_pointer = NULL;
		head->other_bound->queue_pointer = NULL;
	}
	// TODO: Make sure to clean up any resources that were allocated by this library!
	memcpy(return_data, return_node->data, size);
	free_node(return_node);
	return 0;
}

/*
	@brief Internal function that adds node to the queue by actually manipulating the pointers
	@param head - Pointer to the start of the queue
	@param new_node - Pointer to the new node previously initialized
	@return void
*/
void add_node(boundary *head, node *new_node)
{
	// head = head;
	// new_node = new_node;
	// TODO: Splice the pointers to insert the new_node into the queue
	// Hint: Where should the new node go?
	boundary *tail = head->other_bound;
	tail->queue_pointer->next = new_node;
	new_node->prev = tail->queue_pointer;
	new_node->next = NULL;
	tail->queue_pointer = new_node;
}

/*
	@brief Internal helper function that frees all allocated parts of the nodes
	@param node - Node to be freed
*/
void free_node(node *node)
{
	// node = node;
	// TODO: Memory Cleanup
	free(node->id);
	free(node->data);
	free(node);
}
