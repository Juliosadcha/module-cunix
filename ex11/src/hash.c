#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/hash.h"
#include "../include/linked_list.h"

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

void hash_destroy(hashtable_t *ht)
{
  node_t *p;

	for(int i = 0; i < ht->size; i++)
		if(ht->table[i] != NULL){
			p = ht->table[i];
			list_destroy(&p);
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

  while(*key != '\0') {
    sum = sum*9 + *key;
    key++;
  }

  return sum;
}

void hash_set(hashtable_t *ht, char *key, void *ptr)
{
  unsigned int k = hash_func(key) % ht->size, i;
  if (ht->table[k] == NULL){
    ht->table[k] = list_create(key, ptr);
  } else
    list_push(ht->table[k], key, ptr);
}

const void *hash_get(hashtable_t *ht, char *key)
{
  size_t k = hash_func(key) % ht->size;;

  if (ht->table[k] == NULL){
    return NULL;
  }

  node_t *pos = ht->table[k];

  return list_get(pos, key);
}

void hash_print(hashtable_t *ht)
{
  if (!ht)
    return;
  for (int i = 0; i < ht->size; ++i){
    if (ht->table[i] != NULL)
      list_print((node_t *)ht->table[i]);
  }
}

