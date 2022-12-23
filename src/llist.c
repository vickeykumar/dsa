#include<stdio.h>
#include<stdlib.h>
#include <assert.h>
#include <string.h>
#include "error.h"
#include "common.h"
#include "../include/llist.h" 


/*
 * initialize the linked list handle
*/
void llist_new(llist *listhdl, int dataSize, freeFunction freeFn) {
    assert(dataSize>0);
    listhdl->head = listhdl->tail = NULL;
    listhdl->length = 0;
    listhdl->dataSize = dataSize;
    listhdl->freeFn = freeFn; 
}

/*
 * destroys the linkedlist handle
*/
void llist_destroy(llist *listhdl) {
    llNode *curr = NULL;
    while(listhdl->head != NULL) {
        curr = listhdl->head;
        listhdl->head = listhdl->head->next;
        if(listhdl->freeFn) listhdl->freeFn(curr->data);
        free(curr->data);
        free(curr);
        curr=NULL;
        listhdl->length--;
    }
}

/*
adds an element at the begining of the list
*/
void llist_prepend(llist *listhdl, void *data) {
    llNode *node = (llNode*)malloc(sizeof(llNode));
    if (node) {
        node->data = malloc(sizeof(listhdl->dataSize));
        if (!node->data) return;
        memcpy(node->data, data, listhdl->dataSize);
    }
    else {
        printf("unable to allocate memory");
    }

    if(!listhdl->tail) listhdl->tail = node; // first node 
    node->next = listhdl->head;
    listhdl->head=node;
    listhdl->length++;
}

/*
appends an element at the end of list
*/
void llist_append(llist *listhdl, void *data) {
    llNode *node = (llNode*)malloc(sizeof(llNode));
    if (node) {
        node->data = malloc(sizeof(listhdl->dataSize));
        if (!node->data) return;
        memcpy(node->data, data, listhdl->dataSize);
        node->next=NULL;
    }
    else {
        printf("unable to allocate memory");
        return;
    }
    if(listhdl->length==0) {
        listhdl->head = node; //first node
        listhdl->tail=node;
    }
    else {
        listhdl->tail->next=node; //set the link
        listhdl->tail=node;
    }
    listhdl->length++;
}

/* returns the length of the llist
*/
int llist_size(llist *listhdl) {
    return listhdl->length;
}

/*
iterate over all the elements of the llist using the iterate function, 
that recieves the data as void ptr(needs typecast to desired datatype.)
*/
void llist_for_each(llist *listhdl, iterator ll_iterator) {
    assert(ll_iterator != NULL);
    llNode *head = listhdl->head;
    while(head!=NULL) {
        ll_iterator(head->data);
        head=head->next;
    }
}

/*
returns data at head
*/
void llist_head(llist *listhdl, void *data, bool removeFromList) {
    llNode *head = listhdl->head;
    if (!head) return;
    else {
        memcpy(data, head->data, listhdl->dataSize);
        if (removeFromList) {
            llNode *tmp = head;
            head=head->next;
            if (listhdl->freeFn) listhdl->freeFn(tmp->data);
            free(tmp);
            tmp=NULL;
            listhdl->length--;
        }
    }
}

/*
returns data at tail
*/
void llist_tail(llist *listhdl, void *data, bool removeFromList) {
    llNode *tail = listhdl->tail;
    llNode *head = listhdl->head;
    if (!tail) return;
    else {
        memcpy(data, tail->data, listhdl->dataSize);
        if (removeFromList) {
            while (head->next != tail) head=head->next;
            llNode *tmp = tail;
            head->next=NULL;
            if (listhdl->freeFn) listhdl->freeFn(tmp->data);
            free(tmp);
            tmp=NULL;
            listhdl->length--;
        }
    }
}

