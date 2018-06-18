#include <stddef.h>
#include <stdlib.h>
#include "hash.h"
#include "linked_list.h"

hashtable_t *hash_create(unsigned int size)
{
  hashtable_t *new;

	if(size <= 0)
    return NULL;

	new = malloc(sizeof(hashtable_t));
  new->size = size;
  new->table = malloc(size*sizeof(void*));

  for(int i = 0; i < size; i++)
		new->table[i] = NULL;

  return new;
}

void hash_destroy(hashtable_t *ht, void (*fp)(void *data))
{
  node_t *p;

	for(int i = 0; i < ht->size; i++)
		if(ht->table[i] != NULL){
			p = ht->table[i];
			list_destroy(&p, fp);
	  }

	free(ht->table);
	free(ht);
}

unsigned int hash_func(char *key)
{
  int sum, i;

  if (key == NULL){
    return 0;
  }

  sum = 0;

  for (i = 0; *key != '\0'; ++i){
    sum += key[i];
  }

  return sum;
}

void hash_set(hashtable_t *ht, char *key, void *ptr, void (*fp)(void *data))
{
  if (ht == NULL){
    return;
  }

  unsigned int k = hash_func(key) % ht->size, i;
  if (ht->table[k] == NULL){
    ht->table[k] = list_create(ptr);
  }

  list_push(ht->table[k], ptr);
  fp(key);
}

void *hash_get(hashtable_t *ht, char *key)
{
  if (ht == NULL){
    return NULL;
  }

  size_t k = hash_func(key) % ht->size;
  size_t i;

  if (ht->table[k] == NULL){
    return NULL;
  }

  node_t *pos = ht->table[k];

  return pos->data;
}


