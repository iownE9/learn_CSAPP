#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "csapp.h"
#include "cache.h"

/**************************/
/* 方法函数 */
/**************************/
queue init_queue()
{
    init_mutex();
    queue q = Malloc(sizeof(struct linked_list));

    q->start = Malloc(sizeof(struct list_node));
    q->end = Malloc(sizeof(struct list_node));

    q->start->next = q->end;
    q->start->prev = NULL;
    q->start->url = NULL;
    q->start->response = NULL;

    q->end->next = NULL;
    q->end->prev = q->start;
    q->end->url = NULL;
    q->end->response = NULL;

    return q;
}

void free_queue(queue q)
{
    WRITER_IN;

    while (q->start != q->end)
    {
        line node = q->start->next;
        free_node(q->start);
        q->start = node;
    }
    free_node(q->end);

    Free(q);

    WRITER_OUT;
}

void free_node(line node)
{
    if (node->url != NULL)
    {
        Free(node->url);
    }
    if (node->response != NULL)
    {
        Free(node->response);
    }
    TOTAL_P;
    cache_total -= node->size;
    TOTAL_V;
    Free(node);
}

int cache_find(queue q, char *url)
{
    // printf("cache_find(queue q, char *url) %s\n", url);
    reader_in();
    line node = q->start->next;

    while (node != NULL && node != q->end)
    {
        if (!strcmp(node->url, url))
        {
            reader_out();
            // LRU
            cache_LRU(q, node);
            return 1;
        }
        node = node->next;
    }
    reader_out();

    return 0;
}

void new_node(queue q, char *url, char *response, unsigned int size)
{
    if (size > MAX_OBJECT_SIZE)
    {
        return;
    }
    TOTAL_P;
    cache_total += size;
    TOTAL_V;
    while (cache_total > MAX_CACHE_SIZE)
    {
        // LRU
        delete_end_node(q);
    }
    line node = Malloc(sizeof(struct list_node));

    /* '\0' */
    node->url = Malloc(strlen(url) + 1);
    strcpy(node->url, url);

    node->response = Malloc(size + 1);

    strcpy(node->response, response);

    node->size = size;
    // printf("add_start_node\n");
    // LRU
    add_start_node(q, node);
}

void add_start_node(queue q, line node)
{
    WRITER_IN;
    line prev = q->start;
    line next = q->start->next;

    node->prev = prev;
    node->next = next;

    prev->next = node;
    next->prev = node;

    WRITER_OUT;
}

void delete_end_node(queue q)
{
    WRITER_IN;
    line node = q->end->prev;
    if (node == q->start)
    {
        WRITER_OUT;
        return;
    }
    // 移除 node
    line prev = node->prev;
    line next = node->next;
    prev->next = next;
    next->prev = prev;
    free_node(node);

    WRITER_OUT;
}
// LRU  放最前面
void cache_LRU(queue q, line node)
{
    // printf("cache_LRU(queue q, line node)\n");
    if (node == q->start->next)
    {
        return;
    }
    WRITER_IN;

    // 移除 node
    line prev = node->prev;
    line next = node->next;
    prev->next = next;
    next->prev = prev;

    // node 放最前面
    prev = q->start;
    next = q->start->next;
    prev->next = node;
    next->prev = node;
    node->prev = prev;
    node->next = next;

    WRITER_OUT;
}

void init_mutex()
{
    readcnt = 0;
    Sem_init(&mutex, 0, 1);
    Sem_init(&total, 0, 1);
    Sem_init(&w, 0, 1);
}

void reader_in()
{
    P(&mutex);
    readcnt++;
    if (readcnt == 1)
    {
        P(&w);
    }
    V(&mutex);
}

void reader_out()
{
    P(&mutex);
    readcnt--;
    if (readcnt == 0)
    {
        V(&w);
    }
    V(&mutex);
}
