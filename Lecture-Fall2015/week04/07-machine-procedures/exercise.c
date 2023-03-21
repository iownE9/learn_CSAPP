long add5(long b0, long b1, long b2, long b3, long b4)
{
    return b0 + b1 + b2 + b3 + b4;
}
long add10(long a0, long a1, long a2, long a3, long a4, long a5,
           long a6, long a7, long a8, long a9)
{
    return add5(a0, a1, a2, a3, a4) +
           add5(a5, a6, a7, a8, a9);
}
