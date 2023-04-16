//  description: 5.7

#include <stdlib.h>
#include "combine.h"
#include "vec.h"

void unroll5(vec_ptr v, data_t *dest)
{
    long i;
    long length = vec_length(v);
    long limit = length - 4;
    data_t *data = get_vec_start(v);
    data_t acc = IDENT;

    /* Combine 5 elements at a time */
    for (i = 0; i < limit; i += 2)
    {
        acc = (acc OP data[i])OP data[i + 1];
        acc = (acc OP data[i + 2]) OP data[i + 3];
        acc = acc OP data[i + 4];
    }

    /* Finish any remaining elements */
    for (; i < length; i++)
        acc = acc OP data[i];

    *dest = acc;
}