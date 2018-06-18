#include <stdio.h>
#include <stdlib.h>
#include "test.h"

unsigned int my_strlen(char *str)
{
  size_t i;

  for (i = 0; str[i]; i++);

  return i;
}

