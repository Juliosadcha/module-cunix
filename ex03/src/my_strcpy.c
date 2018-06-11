#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "test.h"
char *my_strcpy(char *dest, const char *src)
{
  size_t i = 0;

  for (i; src[i]!= '\0'; i++)
  {
    dest[i] = src[i];
  }
  dest[i] = '\0';
  return dest;
}


