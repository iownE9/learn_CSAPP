/* Demonstration of buffer overflow */

/**
 * 这题的溢出报错很微妙
 * GCC 的升级，导致这份15年的代码编译结果又又又发生变化了 bufdemo-newsp
 */

#include <stdio.h>
#include <stdlib.h>

/* Implementation of library function gets() */
char *gets(char *dest)
{
  int c = getchar();
  char *p = dest;
  while (c != EOF && c != '\n')
  {
    *p++ = c;
    c = getchar();
  }
  *p = '\0';
  return dest;
}

/* Read input line and write it back */
void echo()
{
  char buf[4]; /* Way too small! */
  gets(buf);
  // fgets(buf, 4, stdin);
  puts(buf);
}

void call_echo()
{
  echo();
}

void smash()
{
  printf("I've been smashed!\n");
  exit(0);
}

int main()
{
  printf("Type a string:");
  call_echo();
  return 0;
}
