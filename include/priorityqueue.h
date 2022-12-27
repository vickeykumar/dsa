#ifndef __DSA_PRIORITYQ_H
#define __DSA_PRIORITYQ_H

#include<stdio.h>
#include<stdlib.h>
#include "common.h"

#define MAX_SIZE 1024

typedef struct {
    int key;
    void *payload;
    int payload_size;
} Element;

typedef struct {
    int size;
    Element *pqueue[MAX_SIZE]; //array of pointers to element
    freeFunction freeFn;    // this is free function for payload
} priorityQueue;

priorityQueue* priorityqueue_new(freeFunction freeFn);

void pq_init(priorityQueue* pq, freeFunction freeFn);
void priorityqueue_delete(priorityQueue *pq);
/*int parent(int i);

//! left child of i
int left(int i);

//! right child of i
int right(int i);
*/
//! maintain heap property at i
void pq_max_heapify(priorityQueue* pq, int i);


//!  insert a new element in the heap
void pq_insert(priorityQueue* pq, int key, void *payload, int payload_size);


int pq_extract_max(priorityQueue *pq, void *data);

bool pq_is_empty(priorityQueue *pq);

void pq_for_each(priorityQueue *pq, iterator pq_iterator);
void display_element(void *data);

#endif

