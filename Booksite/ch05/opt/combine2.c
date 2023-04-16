//  description: zh-cn p350

#include <stdlib.h>
#include "combine.h"
#include "vec.h"

/* Implementaion with maximum use of data abstraction */
void combine2(vec_ptr v, data_t *dest)
{
    long i;
    long length = vec_length(v);

    *dest = IDENT;
    for (i = 0; i < length; i++)
    {
        data_t val;
        get_vec_element(v, i, &val);
        *dest = *dest OP val;
    }
}