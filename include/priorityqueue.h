#ifndef __DSA_PRIORITYQ_H
#define __DSA_PRIORITYQ_H

#include<stdio.h>
#include<stdlib.h>
#include "common.h"

#define MAX_SIZE 1024

/**

@brief A structure to represent an element in the priority queue.
@field key The key of the element.
@field payload Pointer to the payload of the element.
@field payload_size The size of the payload.
*/
typedef struct {
    int key;
    void *payload;
    int payload_size;
} Element;

/**

@brief A structure to represent a priority queue.
@field size The number of elements in the priority queue.
@field pqueue Array of pointers to the elements in the priority queue.
@field freeFn A function pointer to be used to free the payload of an element.
@field compare A function pointer to be used to compare the keys of two elements.
*/

typedef struct {
    int size;
    Element *pqueue[MAX_SIZE]; //array of pointers to element
    freeFunction freeFn;    // this is free function for payload
    Comparater compare;    
} priorityQueue;

/**

@brief Create a new priority queue.
@param freeFn A function pointer to be used to free the payload of an element.
@param comp A function pointer to be used to compare the keys of two elements.
default compared on the basis of keys and MAX heap, to set priority other than key use payload to pass the priority 
and use compare function on priority/payload to customize the priority queue.
check graph_algo for demo.
@return A pointer to the newly created priority queue.
*/
priorityQueue* priorityqueue_new(freeFunction freeFn, Comparater comp);

void pq_init(priorityQueue* pq, freeFunction freeFn, Comparater comp);
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
/**

Insert a new element into the priority queue.
@param pq Pointer to the priority queue.
@param key Key of the new element.
@param payload Payload of the new element, NULL for empty payload
@param payload_size Size of the payload.
*/
void pq_insert(priorityQueue* pq, int key, void *payload, int payload_size);

/* update the data to the pq, 
 * will behave like normal increase key or decrease key for respective pq
 */
/**

Updates an existing element into the priority queue.
@param pq Pointer to the priority queue.
@param key Key of the existing element, identified by key.
@param payload Payload of the new element, NULL for empty payload
@param payload_size Size of the payload.
*/
void pq_update(priorityQueue* pq, int key, void *payload, int payload_size);

/**

@brief Extracts the maximum element from the priority queue.
@param pq The priority queue.
@param data A pointer to a location where the data of the extracted element will be stored, send NULL, when not interested in data but only in key 
@return key of the element extracted.
*/
int pq_extract_max(priorityQueue *pq, void *data);
int pq_extract_min(priorityQueue *pq, void *data);

bool pq_is_empty(priorityQueue *pq);

void pq_for_each(priorityQueue *pq, iterator pq_iterator);
void display_pq_element(void *data);

#endif

