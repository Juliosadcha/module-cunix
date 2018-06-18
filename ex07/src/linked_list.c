#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct  node {
    void        *data;
    struct node *next;
}              node_t;

node_t *list_create(void *data){
    node_t *head = (node_t *)malloc(sizeof(node_t));
    head->data = data;
    head->next = NULL;
    return head;
}

void list_destroy(node_t **head, void (*fp)(void *data)){
    if (head == NULL) {
      return;
    }
    node_t *curr = *head;
    node_t *next;

    while (curr != NULL) {
         fp(curr->data);
         next = curr->next;
         free(curr);
         curr = next;
    }
    *head = NULL;
}

void list_push(node_t *head, void *data){
    node_t* tmp = head;
    while(tmp->next != NULL){
        tmp = tmp->next;
    }
    tmp->next = (node_t*) malloc(sizeof(node_t));
    tmp->next->data = data;
    tmp->next->next = NULL;

}

void list_unshift(node_t **head, void *data){
     node_t *new_n = (node_t*)malloc(sizeof(node_t));
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
        free((*head)->data);
        free((*head)->next);
        free(*head);
        *head = NULL;
    } else {
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
        free(elm->data);
        free(elm);
        return d;
    }
}

void list_print(node_t *head){
    node_t * cur = head;
    while (cur != NULL) {
        printf("%s\n", cur->data);
        cur = cur->next;
    }
}

void list_visitor(node_t *head, void (*fp)(void *data)) {
    while (head != NULL) {
        (*fp)(head->data);
        head = head->next;
    }
}
