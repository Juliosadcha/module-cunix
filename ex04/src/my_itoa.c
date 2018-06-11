#include <stdio.h>
#include <stdlib.h>

int power(int num, int p) {
  int res = num;
  for(int i = 1; i < p; i++) {
    num *= res;
  }
  return num;
}

void my_itoa(int num)
{
  int kek = num;
  int length = 0;
  while(kek > 1) {
    kek = kek / 10;
    length++;
  }
  length++;
  char *str = malloc(length * sizeof(char));
  //printf("%d", num / power(10, length - 1));
  for(int i = 0; i < length - 1; i++)
  {
    printf("%d", num / power(10, i));
  }
}

int main() {
  char *str;
  my_itoa(123);
  return 0;
}
