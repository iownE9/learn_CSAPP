#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* For all these problems, you may not use any
 * string library functions; you may, however,
 * define any helper functions that you may need */

/* Concatenates the src string to the end of the dest
 * string, returns the dest string
 *
 * You can assume that src/dest are '\0' terminated,
 * that dest hold enough space to store src+dest and
 * src/dest do not overlap in memory */
char *strcat_m(char *dest, char *src)
{
    /* TODO: Implement this function */
    int dest_len = strlen(dest);
    int src_len = strlen(src);

    for (int i = 0; i < src_len; i++)
        dest[i + dest_len] = src[i];

    dest[src_len + dest_len] = '\0';
    return dest;
}

/* Reverses a string and returns the a new string
 * containing the reversed string
 *
 * You can assume that str is '\0' terminated */
char *strrev(char *str)
{
    /* TODO: Implement this function */
    int str_len = strlen(str);
    char *rev_str = malloc(sizeof(char) * (str_len + 1));

    for (int i = str_len - 1; i >= 0; i--)
        rev_str[str_len - i - 1] = str[i];

    rev_str[str_len] = '\0';
    return rev_str;
}

int main()
{
    /* TODO: Implement test cases to check your implemenation
     * You MAY use string library functions to test your code */
    char *str1 = malloc(sizeof(char) * 10);
    strcpy(str1, "efgh");
    char *str2 = malloc(sizeof(char) * 10);
    strcpy(str2, "abcd");

    strcat_m(str2, str1);
    printf("%s\n", str2); // expect abcdefgh
    char *rev_str1 = strrev(str1);
    printf("%s\n", rev_str1); // expect hgfe

    free(str1);
    free(str2);
    free(rev_str1);
    return 0;
}
