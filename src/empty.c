#include "empty.h"
#include <string.h>

int	is_empty(char *str)
{
  int	i;

  i = 0;
  if (strlen(str) == 0)
    return (1);
  while (str[i] == ' ' && i < (int)strlen(str))
    {
      i++;
    }
  if (i == (int)strlen(str))
    return (1);
  return (0);
}
