#include "list.h"
#include "int_fn_ptrs.h"
#include <stdlib.h>

int main()
{
    list l = new_list(NULL, &print_int, &ints_equal);
    // free(): invalid pointer
    // 只有 malloc 返回的地址才能free(). http://t.csdn.cn/pmtz9
    // 元素是 int  无需 free
    // list l = new_list(&free, &print_int, &ints_equal);
    int x = 42;
    int y = 54;
    int z = 100;
    int w = 13;

    append_node(&x, l);
    append_node(&y, l);

    prepend_node(&z, l);
    prepend_node(&w, l);
    print_list(l);

    int del = *(int *)(delete_nodes(&x, l));
    printf("del= %d\n", del);
    print_list(l);

    map(l, &next_pow_2);
    print_list(l);
    free_list(l);
}
