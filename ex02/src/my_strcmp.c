#include "test.h"

int my_strcmp(char *s1, char *s2)
{
  int flag;
  flag = 0;

  while(*s1 != '\0' || *s2 != '\0'){
    if(*s1 > *s2) {
      flag = 1;
      break;
    }
    else {
      if(*s1 < *s2) {
        flag = -1;
        break;
      }
      else {
        flag = 0;
      }
    }

    s1++;
    s2++;
  }

  return flag;
}

