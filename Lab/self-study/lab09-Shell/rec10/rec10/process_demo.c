#include <stdio.h>
#include <unistd.h>

int main()
{
  int n;
  if (scanf("%d", &n) < 0)
  {
    printf("please input n: ");
  }

  int i = 0;
  for (; i < n; i++)
  {
    printf("%d\n", i);
    sleep(1);
  }
  printf("Done.\n");

  return 0;
}
