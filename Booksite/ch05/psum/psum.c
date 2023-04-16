//  description: zh-cn p346

/* Compute prefix sum of vector a */
void psum1(float a[], float p[], long n)
{
    long i;
    p[0] = a[0];
    for (i = 1; i < n; i++)
        p[i] = p[i - 1] + a[i];
}

void psum2(float a[], float p[], long n)
{
    long i;
    p[0] = a[0];
    for (i = 1; i < n - 1; i += 2)
    {
        float mid_val = p[i - 1] + a[i];
        p[i] = mid_val;
        p[i + 1] = mid_val + a[i + 1];
    }

    if (i < n)
        p[i] = p[i - 1] + a[i];
}

// p387 5_11
void psum1a(float a[], float p[], long n)
{
    long i;
    /* last_val holds p[i-1]; val holds p[i] */
    float last_val, val;
    last_val = p[0] = a[0];

    for (i = 1; i < n; i++)
    {
        val = last_val + a[i];
        p[i] = val;
        last_val = val;
    }
}