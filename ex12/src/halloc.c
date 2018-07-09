#include "halloc.h"

size_t align(size_t size)
{
  return (((((size) -1) >> 2) << 2 ) + 4);
}

void *halloc_base()
{
  block b;
  b = NULL;

  if (!b) {
    b = sbrk(align(sizeof(struct block_meta)));
    if (b == (void*) -1) {
      _exit(127);
    }

    b->size = 0;
    b->next = NULL;
    b->free = 0;
    b->data = NULL;
  }

  return b;
}

block chunk_find(size_t s, block *last)
{
  block c;
  c = halloc_base();

  while (c && !(c->free && c->size >= s)){
    *last = c;
    c = c->next;
  }

  return c;
}

void merge_next(block c)
{
  c->size += c->next->size + sizeof(struct block_meta);
  c->next = c->next->next;
}

void split_next(block c, size_t size)
{
  block newc;

  newc = (block)((char*) c + size);
  newc->next = c->next;
  newc->size = c->size - size;
  newc->free = 1;
  newc->data = (void *)(newc + 1);

  c->next = newc;
  c->size = size - sizeof(struct block_meta);
}

void *halloc(size_t size) {
  if (!size)
    return NULL;

  block c, prev;
  size_t length;

  length = align(size + sizeof(struct block_meta));
  prev = NULL;
  c = chunk_find(size, &prev);

  if (!c) {
    block newc = sbrk(length);
    if (newc == (void*) -1) {
      return NULL;
    }
    newc->next = NULL;
    newc->size = length - sizeof(struct block_meta);
    newc->data = (void *)(newc + 1);
    prev->next = newc;
    c = newc;
  } else if (length + sizeof(size_t) < c->size) {
    split_next(c, length);
  }

  c->free = 0;

  return c->data;
}

void my_free(void *ptr)
{
  if (!ptr || ptr > sbrk(0))
    return;

  block c;
  c = (block) ptr - 1;
  c->free = 1;

  if (c->next)
    merge_next(c);

}

