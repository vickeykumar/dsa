#ifndef __DSA_LINKEDLIST_H
#define __DSA_LINKEDLIST_H

#include<stdlib.h>
#include <assert.h>
#include <string.h>
#include "error.h"
#include "common.h"

typedef struct _llNode {
    void *data;
    struct _llNode *next;
} llNode;

typedef struct _llist {
  llNode *head;
  llNode *tail;
  freeFunction freeFn;
  int length;
  int dataSize;
} llist;

/*
 * initialize the linked list handle
*/
extern void llist_new(llist *listhdl, int dataSize, freeFunction freeFn);

/*
 * destroys the linkedlist handle
*/
void llist_destroy(llist *listhdl);

/*
adds an element at the begining of the list
*/
void llist_prepend(llist *listhdl, void *data);

/*
appends an element at the end of list
*/
void llist_append(llist *listhdl, void *data);

/* returns the length of the llist
*/
int llist_size(llist *listhdl);

/*
iterate over all the elements of the llist using the iterate function, 
that recieves the data as void ptr(needs typecast to desired datatype.)
*/
void llist_for_each(llist *listhdl, iterator ll_iterator);

/*
return data at head 
*/
void llist_head(llist *listhdl, void *data, bool removeFromList);

/*
returns data at tail
*/
void llist_tail(llist *listhdl, void *data, bool removeFromList);

#endif
