#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "binary_tree.h"

node_t *allocnode()
{
  node_t *node = malloc(sizeof(node_t));

  node->key = NULL;
  node->data = NULL;
  node->left = NULL;
  node->right = NULL;

  return node;
}

node_t *insert(node_t *root, char *key, void *data)
{
  if (!root){
    node_t *new_node = allocnode();
    new_node->data = data;
    new_node->key = key;

    return new_node;
  }
  node_t **next = (strcmp(root->key,key) > 0) ? (next = &root->left ): (next = &root->right);
  *next = insert(*next, key, data);

  return root;
}

void print_node(node_t *node)
{
  if (!node){
    return;
  }

  print_node(node->left);
  print_node(node->right);
  printf("%s : %s\n", node->data, node->key);
}

char* tostr(void *ptr)
{
  return ptr;
}

void print_cstr_node(node_t *n)
{
  printf("[%s] = %s\n", n->key, tostr(n->data));
}

void visit_tree(node_t *node, void (*fp)(node_t *root))
{
  if (!node){
    return;
  }

  visit_tree(node->left, fp);
  fp(node);
  visit_tree(node->right, fp);
}

void fdestroy(node_t *root){
  free(root->data);
  free(root->key);
  free(root->right);
  free(root->left);
  free(root);
}

void destroy_tree(node_t *node, void (*fdestroy)(node_t *root))
{
  if (!node){
    return;
  }

  destroy_tree(node->right, fdestroy);
  destroy_tree(node->left, fdestroy);
  fdestroy(node);
}

