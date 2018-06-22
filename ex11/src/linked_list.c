#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../include/linked_list.h"

node_t *list_create(char *key, void *data)
{
    node_t *head = (node_t *)malloc(sizeof(node_t));
    head->key = key;
    head->data = data;
    head->next = NULL;
    return head;
}

void list_destroy(node_t **head)
{
    if (head == NULL) {
      return;
    }
    node_t *curr = *head;
    node_t *next;

    while (curr != NULL) {
         free(curr->key);
         free(curr->data);
         next = curr->next;
         free(curr);
         curr = next;
    }
    *head = NULL;
}

void list_push(node_t *head, char *key, void *data){
    if (!head)
      return;
    node_t* tmp = head;
    while (tmp->next) {
        if (strcmp(key, (char *)tmp->key) == 0) {
            free(tmp->data);
            free(key);
            tmp->data = data;

            return;
        }
        tmp = tmp->next;
    }
    if (strcmp(key, (char*)tmp->key) == 0) {
        free(tmp->data);
        free(key);
        tmp->data = data;
        return;
    }
    tmp->next = (node_t*) malloc(sizeof(node_t));
    tmp->next->key = key;
    tmp->next->data = data;
    tmp->next->next = NULL;
}

void list_unshift(node_t **head, char *key, void *data){
     node_t *new_n = (node_t*)malloc(sizeof(node_t));
     new_n->key = key;
     new_n->data = data;
     new_n->next = *head;
     *head = new_n;
}

void *list_pop(node_t **head){
    void *ret_val = (void*)-1;

    node_t *prev = NULL;
    if (*head == NULL)
        return (void *)-1;

    prev = (*head)->next;
    ret_val = (*head)->data;
    free((*head)->data);
    free((*head)->key);
    free(*head);
    *head = prev;

    return ret_val;
}


void *list_shift(node_t **head){
    node_t *pFwd = NULL;
    node_t *pBwd = NULL;
    if (!head) {
        exit(-1);
    }

    if (!(*head)) {
        exit(-1);
    }

    pFwd = *head;
    while (pFwd->next) {
        pBwd = pFwd;
        pFwd = pFwd->next;
    }

    if (pBwd == NULL) {
        free((*head)->key);
        free((*head)->data);
        free((*head)->next);
        free(*head);
        *head = NULL;
    } else {
        free((*head)->key);
        free(pFwd->data);
        free(pFwd->next);
        pBwd->next = NULL;
    }
}

node_t * get_n(node_t *head, int n){
    int cnt = 0;
    while (cnt < n && head){
        head = head->next;
        cnt++;
    }
    return head;
}

void *list_remove(node_t **head, int pos){
    if (pos == 0) {
        return list_pop(head);
    } else {
        node_t *prev = get_n(*head, pos - 1);
        node_t *elm  = prev->next;
        void *d = elm->data;

        prev->next = elm->next;
        free(elm->key);
        free(elm->data);
        free(elm);
        return d;
    }
}

void list_print(node_t *head){
    node_t * cur = head;
    while (cur) {
        write(1, cur->key, strlen(cur->key));
        write(1, ": ", 2);
        write(1, cur->data, strlen(cur->data));
        write(1, "\n", 1);
        cur = cur->next;
    }
}

const void *list_get(node_t *head, char *key)
{
    while (head) {
        if (strcmp(key, (char *)head->key) == 0){
            return head->data;
        }
        head = head->next;
    }
    return NULL;
}

