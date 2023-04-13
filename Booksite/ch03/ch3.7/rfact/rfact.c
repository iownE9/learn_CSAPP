/**
 * referenceURL: zh-cn 175
 * *
 * Environment: Linux
 * Compilation: gcc -Og -S rfact.c
 * *
 * Compilation: gcc -O1 -S rfact.c -o rfact_O1.s
 * *
 * description:
 **/

long rfact(long n)
{
    long result;
    if (n <= 1)
        result = 1;
    else
        result = n * rfact(n - 1);
    return result;
}