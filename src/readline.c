#include "readline.h"
#include <stdlib.h>
#include <unistd.h>

#define BUFFER 4096

char	*readline()
{
  char	*buf;
  int	n;
  
  if ((buf = malloc(sizeof(*buf) * (BUFFER + 1))) == 0)
    {
      return (0);
    }
  if ((n = read(0, buf, BUFFER)) > 0)
    {
      buf[n - 1] = 0;
    }
  else
    {
      buf[0] = 0;
    }
  return (buf);
}
