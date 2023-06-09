//  description: zh-cn p355

#include <stdlib.h>
#include "combine.h"
#include "vec.h"

/* Direct acess to vector data */
void combine4(vec_ptr v, data_t *dest)
{
    long i;
    long length = vec_length(v);
    data_t *data = get_vec_start(v);

    data_t acc = IDENT;
    for (i = 0; i < length; i++)
        acc = acc OP data[i];

    *dest = acc;
}