#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/filler.h"
#include "../include/my_string.h"

stream_t        *string_init()
{
  stream_t *str_ptr;

  str_ptr = (stream_t *)malloc(sizeof(stream_t));

  str_ptr->str = NULL;
  str_ptr->size = 0;
  str_ptr->limit = 0;

  return str_ptr;
}

stream_t        *string_create(char* str)
{
  stream_t *str_ptr;
  int len, i;

  str_ptr = string_init();
  len = strlen(str);
  str_ptr->limit = BUF_SIZE;

  while (str_ptr->limit < len){
    str_ptr->limit += BUF_SIZE;
  }

  str_ptr->str = (char *)realloc(str_ptr->str, str_ptr->limit * sizeof(char));

  for (i = 0; i < len; ++i){
    str_ptr->str[str_ptr->size + i] = str[i];
  }

  str_ptr->size += len;
  str_ptr->str[str_ptr->size + len] = 0;

  return str_ptr;
}

void            string_append(stream_t *ptr, char* str)
{
  int i, len;

  len = strlen(str);

  while (ptr->limit < ptr->size + len) {
    ptr->limit += BUF_SIZE;
    ptr->str = (char *)realloc(ptr->str, ptr->limit * sizeof(char));
    ptr->str[ptr->size + len] = 0;
  }

  for (i = 0; i < len; ++i){
    ptr->str[ptr->size + i] = str[i];
  }

  ptr->size += len;
  ptr->str[ptr->size + len] = 0;

}

void            string_destroy(stream_t *str)
{
  free(str->str);
  free(str);
}

