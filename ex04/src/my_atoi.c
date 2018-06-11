#include "test.h"

int is_num(char s)
{
  if (s >= '0' && s <= '9')
    return 1;
  else
    return 0;
}


int my_atoi(const char *str)
{
  int sign = 0;
  int result = 0;
  if(*str == '-') {
    sign = 1;
  } else {
    sign = 0;
  }
  if (!str)
    return 0;
  for (int i = sign; str[i] != '\0'; ++i)
  {
    if(is_num(str[i]) == 1)
      result = result*10 + str[i] - '0';
    else
      break;
  }
  if(sign == 1) {
    result = -1 * result;
  }
  return result;
}

