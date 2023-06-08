/*
 * mm-naive.c - The fastest, least memory-efficient malloc package.
 *
 * In this naive approach, a block is allocated by simply incrementing
 * the brk pointer.  A block is pure payload. There are no headers or
 * footers.  Blocks are never coalesced or reused. Realloc is
 * implemented directly using mm_malloc and mm_free.
 *
 * NOTE TO STUDENTS: Replace this header comment with your own header
 * comment that gives a high level description of your solution.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "mm.h"
#include "memlib.h"

#include <math.h> /* 添加 */
/*********************************************************
 * NOTE TO STUDENTS: Before you do anything else, please
 * provide your team information in the following struct.
 ********************************************************/
team_t team = {
    /* Team name */
    "ALPHA",
    /* First member's full name */
    "Han Lei",
    /* First member's email address */
    "iownE9@163.com",
    /* Second member's full name (leave blank if none) */
    "",
    /* Second member's email address (leave blank if none) */
    ""};

/* single word (4) or double word (8) alignment */
#define ALIGNMENT 8

/* rounds up to the nearest multiple of ALIGNMENT 向上舍入 8的倍数 */
#define ALIGN(size) (((size) + (ALIGNMENT - 1)) & ~0x7)

/* 头尾空间 8 */
#define SIZE_T_SIZE (ALIGN(sizeof(size_t)))

/*********************************************************
 * 自定义区域 start
 ********************************************************/
/***************************
 * Global variables start
 ***************************/
/*
 * you are allowed to declare global scalar variables such
 * as integers, floats, and pointers in mm.c */
static char *heap_listp = NULL; /* Pointer to first block */
static char *free_listp = NULL; /* Pointer to free seglist */

/***************************
 * Global variables end
 ***************************/

/* 宏 */
#define WSIZE 4
#define DSIZE 8
#define MINSIZE 24 /* 两个指针 16 + 头尾 8 */
#define DEBUG 0    /* 开启格式检查 */
#define SEGNUM 9   /* 九类 */
#define OFFSET 4   /* 索引偏移 */
/*
free_listp[0]  5    24 <= size < 32
free_listp[1]  6    ~64
free_listp[2]  7    ~128
free_listp[3]  8    ~256
free_listp[4]  9    ~512
free_listp[5]  10   ~1024
free_listp[6]  11   ~2048
free_listp[7]  12   ~4096
free_listp[8]       4096~  */
#define N_IDX(size) (((int)(log(size) / log(2))) - OFFSET)
#define MAX(x) (((x) < (SEGNUM)) ? (x) : (SEGNUM - 1))
#define GET_N(size) (MAX(N_IDX(size)))

#define GET_SEGLIST(n) (((unsigned long *)free_listp) + (2 * n))

// 头部块大小
#define HEADER ((4 * WSIZE) + (2 * SEGNUM * DSIZE))
/* 读写 p 地址一字大小的内容*/
#define GET(p) (*(unsigned int *)(p))
#define PUT(p, val) ((GET(p)) = ((unsigned int)(val)))

/* 构造信息: 大小 是否分配*/
#define PACK(size, alloc) ((size) | (alloc))
/* size = 负载 + 头尾 */

/* 获取块信息 */
#define GET_SIZE(p) (GET(p) & ~0x7)
#define GET_ALLOC(p) (GET(p) & 0x1)

/* 获取free块信息 */
#define GET_PREV(p) (*(unsigned long *)(p))
#define GET_NEXT(p) (*((unsigned long *)(p) + 1))
#define PUT_PREV(p, val) ((GET_PREV(p)) = ((unsigned long)(val)))
#define PUT_NEXT(p, val) ((GET_NEXT(p)) = ((unsigned long)(val)))

/* 根据负载地址bp 获取块首尾地址 */
#define HDRP(bp) (((char *)(bp)) - WSIZE)
#define FTRP(bp) (((char *)(bp)) + GET_SIZE(HDRP(bp)) - DSIZE)

/* 根据负载地址bp 获取前后块负载地址 */
#define NEXT_BLKP(bp) (((char *)(bp)) + GET_SIZE(HDRP(bp)))
#define PREV_BLKP(bp) (((char *)(bp)) - GET_SIZE(((char *)(bp)) - DSIZE))

/***************************
 * 自定义静态功能函数 start
 ***************************/

static void *coalesce(void *bp);           /* 合并空闲块 */
static void *find_fit(size_t asize);       /* 寻找合适的空闲块 */
static void place(void *bp, size_t asize); /* 放到对应的空闲块中 */
static void *extend_heap(size_t newsize);  /* 申请新堆空间 */

static void checkheap(int verbose); /* 检查堆结构 */
static void printblock(void *bp);   /* 打印块结构 */
static void checkblock(void *bp);   /* 检查块结构 */

static void delete_free(void *delfp); /* 删除free块 */
static void add_free(void *fp);       /* 添加free块 */

/***************************
 * 自定义静态功能函数 end
 **************************/

/*********************************************************
 * 自定义区域 end
 ********************************************************/

/*
 * mm_init - initialize the malloc package. */
int mm_init(void)
{
    /* 初始化堆哨兵 start */
    int i = 0, n = (HEADER / WSIZE) - 2;

    if ((heap_listp = mem_sbrk(HEADER)) == (void *)-1)
    {
        return -1;
    }

    PUT(heap_listp, 0);                                     /* 双字对齐填充 */
    PUT(heap_listp + (1 * WSIZE), PACK(HEADER - DSIZE, 1)); /* 序言头 */

    /* seglist root start */
    for (i = 2; i < n; i++)
    {
        PUT(heap_listp + (i * WSIZE), 0);
    }
    /* seglist root end */

    PUT(heap_listp + (i * WSIZE), PACK(HEADER - DSIZE, 1)); /* 序言尾 */
    PUT(heap_listp + ((i + 1) * WSIZE), PACK(0, 1));        /* 结尾块 */
    /* 初始化堆哨兵 end */

    heap_listp += DSIZE;
    free_listp = heap_listp;

    return 0;
}

/*
 * mm_malloc - Allocate a block by incrementing the brk pointer.
 *     Always allocate a block whose size is a multiple of the alignment. */
void *mm_malloc(size_t size)
{
    /* 忽略无意义请求 */
    if (size <= 0)
    {
        return NULL;
    }

    size_t newsize = ALIGN(size + SIZE_T_SIZE); /* 块字节大小  负载双字对齐 */
    if (newsize < MINSIZE)
    {
        newsize = MINSIZE;
    }
    void *bp; /* 指向负载的地址 */

    /* 先从空闲块中寻找适配 */
    if ((bp = find_fit(newsize)) != NULL)
    {
        delete_free(bp);

        place(bp, newsize);
        if (DEBUG)
        {
            checkheap(1);
        }

        return bp;
    }

    /* 申请新空间 */
    if ((bp = extend_heap(newsize)) == NULL)
    {
        return NULL;
    }

    place(bp, newsize);

    if (DEBUG)
    {
        checkheap(1);
    }
    return bp;
}

/*
 * mm_free - Freeing a block does nothing. */
void mm_free(void *ptr)
{
    if (ptr == 0 || ptr == NULL)
    {
        return;
    }

    /* 获取块大小 */
    size_t size = GET_SIZE(HDRP(ptr));
    /* 头尾分配标识置为 0  */
    PUT(HDRP(ptr), PACK(size, 0));
    PUT(FTRP(ptr), PACK(size, 0));

    /* 合并空闲块 */
    add_free(coalesce(ptr));

    if (DEBUG)
    {
        checkheap(1);
    }
}

/*
 * mm_realloc - Implemented simply in terms of mm_malloc and mm_free */
void *mm_realloc(void *ptr, size_t size)
{
    /* If size == 0 then this is just free, and we return NULL. */
    if (size == 0)
    {
        mm_free(ptr);
        return 0;
    }

    /* If oldptr is NULL, then this is just malloc. */
    if (ptr == NULL)
    {
        return mm_malloc(size);
    }

    size_t newsize = ALIGN(size + SIZE_T_SIZE); /* 需要重新分配的大小 */
    if (newsize < MINSIZE)
    {
        newsize = MINSIZE;
    }
    size_t oldsize = GET_SIZE(HDRP(ptr)); /* 之前分配的大小 */

    if (newsize <= oldsize)
    {
        delete_free(ptr);
        place(ptr, newsize);
        return ptr;
    }

    /* 需置换到新空间 */
    void *newptr = mm_malloc(size);
    /* If realloc() fails the original block is left untouched  */
    if (newptr == NULL)
    {
        return 0;
    }

    /* Copy the old data. */
    memcpy(newptr, ptr, (oldsize - DSIZE));

    /* Free the old block. */
    mm_free(ptr);

    return newptr;
}

/***************************************
 * possibly define other privatestatic functions
 * 自定义的静态功能函数 start
 **************************************/

/* 合并空闲块 start
 * 要求 bp 不在 free_listp 中 */
static void *coalesce(void *bp)
{
    size_t prev_alloc = GET_ALLOC(HDRP(PREV_BLKP(bp)));
    size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
    size_t size = GET_SIZE(HDRP(bp));

    if (prev_alloc && next_alloc)
    { /* 前后都已分配 */
        return bp;
    }
    else if (prev_alloc && !next_alloc)
    { /* 后为free */
        delete_free(NEXT_BLKP(bp));

        size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
        /* 第一种 写法*/
        // PUT(HDRP(bp), PACK(size, 0));
        // PUT(FTRP(bp), PACK(size, 0));
        // /* PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0)); // ERROR！*/

        /* 第二种 写法 */
        PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
        PUT(HDRP(bp), PACK(size, 0));
        return bp;
    }
    else if (!prev_alloc && next_alloc)
    { /* 前为free */
        delete_free(PREV_BLKP(bp));

        size += GET_SIZE(HDRP(PREV_BLKP(bp)));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        PUT(FTRP(bp), PACK(size, 0));
        return (void *)PREV_BLKP(bp);
    }
    else
    { /* 前后均free */
        delete_free(NEXT_BLKP(bp));
        delete_free(PREV_BLKP(bp));

        size += GET_SIZE(HDRP(PREV_BLKP(bp))) + GET_SIZE(HDRP(NEXT_BLKP(bp)));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
        return (void *)PREV_BLKP(bp);
    }
}
/* 合并空闲块 end */

/* 寻找合适的空闲块 start */
static void *find_fit(size_t asize)
{
    // 循环终止处 最后一个free块 GET_NEXT(fp)=0
    for (int n = GET_N(asize); n < SEGNUM; n++)
    {
        unsigned long *seg_listn = GET_SEGLIST(n);
        for (unsigned long fp = GET_NEXT(seg_listn); fp != 0; fp = GET_NEXT(fp))
        {
            if (asize <= GET_SIZE(HDRP(fp)))
            {
                return (void *)fp;
            }
        }
    }

    return NULL; /* No fit */
}
/* 寻找合适的空闲块 end */

/* 放到对应的空闲块中 start
 * 要求 bp 不在 free_listp 中 */
static void place(void *bp, size_t asize)
{
    size_t csize = GET_SIZE(HDRP(bp));

    /* 剩余空间是否满足最小块需求 MINSIZE */
    if ((csize - asize) >= MINSIZE)
    {
        PUT(HDRP(bp), PACK(asize, 1));
        PUT(FTRP(bp), PACK(asize, 1));

        void *fp = NEXT_BLKP(bp);
        PUT(HDRP(fp), PACK(csize - asize, 0));
        PUT(FTRP(fp), PACK(csize - asize, 0));
        add_free(fp);
    }
    else
    {
        PUT(HDRP(bp), PACK(csize, 1));
        PUT(FTRP(bp), PACK(csize, 1));
    }
}
/* 放到对应的空闲块中 end */

/* 申请新堆空间 start */
static void *extend_heap(size_t newsize)
{
    /* 申请空间的字节大小*/
    void *bp = mem_sbrk(newsize);
    if (bp == (void *)-1)
    {
        return NULL;
    }
    /* 初始化新块的头尾 */
    PUT(HDRP(bp), PACK(newsize, 1));
    PUT(FTRP(bp), PACK(newsize, 1));

    /* 新的结尾块 */
    PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1));

    /* 若前一块为空，合并 */
    return coalesce(bp);
}
/* 申请新堆空间 end */

/* 后进先出 start */
/* 删除free块 */
static void delete_free(void *delfp)
{
    size_t size = GET_SIZE(HDRP(delfp));
    unsigned long *seg_listn = GET_SEGLIST(GET_N(size));
    // 循环终止处 最后一个free块 GET_NEXT(fp)=0
    for (unsigned long fp = GET_NEXT(seg_listn); fp != 0; fp = GET_NEXT(fp))
    {
        if (((unsigned long)fp) == ((unsigned long)delfp))
        {
            unsigned long prev = GET_PREV(fp);
            unsigned long next = GET_NEXT(fp);

            PUT_NEXT(prev, next);

            if (next != 0)
            {
                PUT_PREV(next, prev);
            }
        }
    }
}

/* 添加free块 */
static void add_free(void *fp)
{
    int n = GET_N(GET_SIZE(HDRP(fp)));
    unsigned long *seg_listn = GET_SEGLIST(n);

    unsigned long next = GET_NEXT(seg_listn);
    PUT_NEXT(seg_listn, fp);

    PUT_NEXT(fp, next);
    PUT_PREV(fp, seg_listn);

    if (next != 0)
    {
        PUT_PREV(next, fp);
    }
}
/* 后进先出 end */

/* 检查堆结构 */
static void checkheap(int verbose)
{
    char *bp = heap_listp;

    if (verbose)
    {
        printf("Heap (%p):\n", heap_listp);
    }
    /* 头尾块 */
    if ((GET_SIZE(HDRP(heap_listp)) != (HEADER - DSIZE)) || !GET_ALLOC(HDRP(heap_listp)))
    {
        printf("Bad prologue header\n");
    }

    checkblock(heap_listp);

    for (bp = heap_listp; GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp))
    {
        if (verbose)
        {
            printblock(bp);
        }
        checkblock(bp);
    }

    /* 结尾块 */
    if (verbose)
    {
        printblock(bp);
    }
    if ((GET_SIZE(HDRP(bp)) != 0) || !(GET_ALLOC(HDRP(bp))))
    {
        printf("Bad epilogue header\n");
    }
}

/* 打印块结构 */
static void printblock(void *bp)
{
    size_t hsize, halloc, fsize, falloc;

    hsize = GET_SIZE(HDRP(bp));
    halloc = GET_ALLOC(HDRP(bp));
    fsize = GET_SIZE(FTRP(bp));
    falloc = GET_ALLOC(FTRP(bp));

    if (hsize == 0)
    {
        printf("%p: EOL\n", bp);
        return;
    }

    printf("%p: header: [%x:%c] footer: [%x:%c]\n", bp,
           hsize, (halloc ? 'a' : 'f'),
           fsize, (falloc ? 'a' : 'f'));
}

static void checkblock(void *bp)
{
    if ((size_t)bp % 8)
    {
        printf("Error: %p is not doubleword aligned\n", bp);
        printblock(bp);
    }
    if (GET(HDRP(bp)) != GET(FTRP(bp)))
    {
        printf("Error: header does not match footer\n");
        printblock(bp);
    }
}
/***************************************
 * 自定义的静态功能函数 end
 **************************************/