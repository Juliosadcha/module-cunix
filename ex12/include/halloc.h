#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

typedef struct block_meta *block;

struct block_meta {
  size_t size;
  block next;
  int free;
  char *data;
};


void *halloc (size_t size);
void my_free(void *ptr);

