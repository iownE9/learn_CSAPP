#include "cachelab.h"
#include "cachelab.h"
#include <getopt.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/**************************/
/* Node Types */
/**************************/
typedef struct linked_list *queue;
typedef struct list_node *line;

struct list_node
{
    int v;
    unsigned long tag;
    // unsigned long blockIndex;
    line next;
    line prev;
};

struct linked_list
{
    line start; // 首哨兵
    line end;   // 尾哨兵
    int size;   // line数
};

static int verbose = 0;
// 统计 start
static int hits = 0;      /* number of  hits */
static int misses = 0;    /* number of misses */
static int evictions = 0; /* number of evictions */
// 统计 end

/**************************/
/* 函数签名 */
/**************************/
void free_cache(queue *cache, int size);
void print_valid_commands();
void print_valid_access();
//
queue init_queue(int E);
void free_queue(queue q);
void cache_load(queue q, unsigned long tag);
void cache_store(queue q, unsigned long tag);
void cache_modify(queue q, unsigned long tag);
//
void cache_LRU(queue q, line node);

/**************************/
/* main */
/**************************/
int main(int argc, char *argv[])
{

    int test = 0; // 开启输出？

    // 命令行参数 start
    extern char *optarg;
    // extern int optind, opterr, optopt;

    int errorFlag = 0;

    char arg;

    int s = -1;
    int E = -1;
    int b = -1;
    char *t = ""; // 测试文件
    char *optstring = "hfvs:E:b:t:";

    while ((arg = getopt(argc, argv, optstring)) != -1)
    {
        switch (arg)
        {
        case 'v':
            verbose = 1;
            break;
        case 'h':
            print_valid_commands();
            exit(0);
        case 's':
            s = atoi(optarg);
            break;
        case 'E':
            E = atoi(optarg);
            break;
        case 'b':
            b = atoi(optarg);
            break;
        case 't':
            t = optarg;
            break;
        // 自定义 是否开启跟踪
        case 'f':
            test = 1;
            break;
        default:
            errorFlag = 1;
            break;
        }
    }

    if (errorFlag || s <= 0 || E <= 0 || b <= 0)
    {
        printf("Error: invalid arguments\n");
        exit(errorFlag);
    }

    if (test)
    {
        printf("test: ./csim -v %d -s %d -E %d -b %d -t %s\n", verbose, s, E, b, t);
    }
    // 命令行参数 end

    // 构造 cache start
    // 每个组对应一个队列，2^s 组 -> queue[2^s]
    // 组内的 line 数对应 节点数，LRU
    int n = (1 << s);

    queue *cache = malloc(sizeof(queue) * n);

    if (cache == NULL)
    {
        fprintf(stderr, "allocation failed\n");
        exit(1);
    }
    // 每个 queue 有 E 个 line
    for (size_t i = 0; i < n; i++)
    {
        // // -1 -> allocation failed
        // if (init_queue(cache[i], E) < 0)
        // {
        //     fprintf(stderr, "allocation failed\n");
        //     free_cache(cache, i);
        //     exit(1);
        // }
        cache[i] = init_queue(E);
        // init_queue(cache[i], E); // 值传递
    }
    // 构造 cache end

    // 读文件 start
    FILE *pFile = fopen(t, "r");
    if (!pFile)
    {
        fprintf(stderr, "cannot open %s for reading\n", t);
        free_cache(cache, n);
        exit(1);
    }

    char access_type;
    unsigned long address;
    int size;
    int read = 0;

    while ((read = fscanf(pFile, " %c %lx,%d", &access_type, &address, &size)) != EOF)
    {

        // 验证文件格式 start
        if (read != 3) // failed to match
        {
            fprintf(stderr, "Invalid file format in file %s\n", t);
            free_cache(cache, n);
            fclose(pFile);
            exit(1);
        }
        if (verbose)
        {
            printf("%c %lx,%d", access_type, address, size);
        }
        // 验证 文件格式 end

        // ignore all instruction cache accesses start
        if (access_type == 'I')
            continue;
        // ignore all instruction cache accesses end

        // 解析 address start
        unsigned long tag = (address) >> (s + b);
        unsigned long setIndex = (address >> b) & ((1 << s) - 1);
        if (test)
        {
            unsigned long blockIndex = (address) & ((1 << b) - 1);
            printf("  test: tag=%lx setIndex=%lx blockIndex=%lx  ", tag, setIndex, blockIndex);
        }
        // 解析 address end

        // 执行 access start
        switch (access_type)
        {
        case 'M':
            cache_modify(cache[setIndex], tag);
            break;
        case 'L':
            cache_load(cache[setIndex], tag);
            break;
        case 'S':
            cache_store(cache[setIndex], tag);
            break;
        default:
            print_valid_access();
            free_cache(cache, n);
            fclose(pFile);
            exit(1);
        }
        printf(" \n");
    }

    fclose(pFile);
    // 读文件 end

    // free
    free_cache(cache, n);

    // sum
    printSummary(hits, misses, evictions);
    return 0;
}

/**************************/
/* 方法函数 */
/**************************/
// 暂不进行 allocation failed 判定
queue init_queue(int size)
{
    queue q = malloc(sizeof(struct linked_list));
    q->size = size;

    q->start = malloc(sizeof(struct list_node));
    q->end = malloc(sizeof(struct list_node));
    q->end->v = 0;

    q->start->next = q->end;
    q->end->prev = q->start;

    for (size_t i = 0; i < size; i++)
    {
        line node = malloc(sizeof(struct list_node));
        node->v = 0; // 有效位

        // add at end
        line next = q->end;
        line prev = q->end->prev;

        next->prev = node;
        node->next = next;
        prev->next = node;
        node->prev = prev;
    }

    return q;
}

void free_queue(queue q)
{
    while (q->start != q->end)
    {
        line node = q->start->next;
        free(q->start);
        q->start = node;
    }
    free(q->end);

    free(q);
}

void cache_load(queue q, unsigned long tag)
{
    line node = q->start->next;

    while (node->v)
    {
        if (node->tag == tag)
        {
            hits++;
            if (verbose)
            {
                printf(" hit");
            }
            // LRU
            cache_LRU(q, node);
            return;
        }
        node = node->next;
    }
    if (node != q->end)
    {
        node->v = 1;
        node->tag = tag;
        misses++;
        cache_LRU(q, node);
        if (verbose)
        {
            printf(" miss");
        }
    }
    else
    {
        node = node->prev;
        node->tag = tag;
        evictions++;
        misses++;
        cache_LRU(q, node);
        if (verbose)
        {
            printf(" miss eviction");
        }
    }
}
void cache_store(queue q, unsigned long tag)
{
    cache_load(q, tag);
}
void cache_modify(queue q, unsigned long tag)
{
    cache_load(q, tag);
    cache_store(q, tag);
}

// LRU  放最前面
void cache_LRU(queue q, line node)
{
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
}
/**************************/
/* 工具函数 */
/**************************/
void print_valid_commands()
{
    printf("• -h: Optional help flag that prints usage info\n");
    printf("• -v: Optional verbose flag that displays trace info\n");
    printf("• -s <s>: Number of set index bits(S = 2 ^ s is the number of sets)\n");
    printf("• -E <E>: Associativity (number of lines per set)\n");
    printf("• -b <b>: Number of block bits (B = 2^bis the block size)\n");
    printf("• -t <tracefile>: Name of the valgrind trace to replay\n");
}

void print_valid_access()
{
    fprintf(stderr, "Valid commands: \n");
    fprintf(stderr, "L:   data load\n");
    fprintf(stderr, "S:   data store\n");
    fprintf(stderr, "M:   data modify (i.e., a data load followed by a data store)\n");
    fprintf(stderr, "I:   Instruction load\n");
}

void free_cache(queue *cache, int n)
{
    for (size_t i = 0; i < n; i++)
    {
        free_queue(cache[i]);
    }
    free(cache);
}
