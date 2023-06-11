#ifndef __CACHE_H__
#define __CACHE_H__

#include "csapp.h"

/* Recommended max cache and object sizes */
#define MAX_CACHE_SIZE 1049000
#define MAX_OBJECT_SIZE 102400

/* 读者优先 */
static int readcnt;
static sem_t mutex, w, total;
#define WRITER_IN P(&w)
#define WRITER_OUT V(&w)

#define TOTAL_P P(&total)
#define TOTAL_V V(&total)

/* only count bytes used to store the actual web objects
   即只统计 respones 的大小 node->size */
static unsigned int cache_total = 0;
/**************************/
/* Node Types */
/**************************/
typedef struct linked_list *queue;
typedef struct list_node *line;

struct list_node
{
    char *url;
    char *response;
    unsigned int size;
    line next;
    line prev;
};

struct linked_list
{
    line start; // 首哨兵
    line end;   // 尾哨兵
};

/**************************/
/* 函数签名 */
/**************************/
queue init_queue();
void free_queue(queue q);
void free_node(line node);
int cache_find(queue q, char *url);
void new_node(queue q, char *url, char *response, unsigned int size);
void add_start_node(queue q, line node);
void delete_end_node(queue q);
// LRU放最前面
void cache_LRU(queue q, line node);

void init_mutex();
void reader_out();
void reader_in();

#endif /* __CACHE_H__ */
