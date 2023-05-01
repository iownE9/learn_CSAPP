#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
  // char *input = malloc(sizeof(char) * 5);
  char *input = (char *)calloc((5 + 1), sizeof(char));
  if (input == NULL)
    return 0;

  if (strcmp(input, "\x00\x00\x00\x00\x00") != 0)
  {
    printf("memory error\n");
  }

  printf("Input your 5-digit Pin: ");
  scanf("%5s", input);

  if (strcmp("15213", input) == 0)
  {
    printf("Access Granted\n");
    printf("1. C, 2. C, 3. C, 4. C, 5. C\n");
  }
  else
  {
    printf("Access Denied\n");
  }

  free(input);
  return 0;
}
