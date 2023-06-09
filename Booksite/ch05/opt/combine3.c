// referenceURL: zh-cn p354

#include <stdlib.h>
#include "combine.h"
#include "vec.h"

/* Direct acess to vector data */
void combine3(vec_ptr v, data_t *dest)
{
    long i;
    long length = vec_length(v);
    data_t *data = get_vec_start(v);

    *dest = IDENT;
    for (i = 0; i < length; i++)
        *dest = *dest OP data[i];
}