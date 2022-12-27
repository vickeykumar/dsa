#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include "priorityqueue.h"

void swap_Element(Element **arr, int i, int j) {
    Element *tmp=arr[i];
    arr[i]=arr[j];
    arr[j]=tmp;
}

void display_element(void *data) {
    Element *e = (Element*)data;
    printf("%d -> %p\n", e->key, e->payload);
}

priorityQueue* priorityqueue_new(freeFunction freeFn) {
    priorityQueue* pq = (priorityQueue*)malloc(sizeof(priorityQueue));
    pq->size = 0;
    pq->freeFn=freeFn;
    return pq;
}

// Function to initialize the heap
void pq_init(priorityQueue* pq, freeFunction freeFn) {
  pq->size = 0;
  pq->freeFn = freeFn;
}


void pq_delete(priorityQueue* pq) {
    while (pq->freeFn && pq->size>0) {
        pq->freeFn(pq->pqueue[pq->size]->payload);
        pq->size--;
    }
    if(pq) free(pq);
    pq=NULL;
}
static int parent(int i) { return (i-1)/2; }

//! left child of i
static int left(int i) { return 2*i+1; }

//! right child of i
static int right(int i) { return 2*i+2; }

//! maintain heap property at i
void pq_heapify(priorityQueue* pq, int i) {
    int largestchild =i;
    int leftchild = left(i);
    int rightchild = right(i);

    //! find largest childs index
    if(leftchild<pq->size && pq->pqueue[leftchild]->key > pq->pqueue[i]->key) largestchild = leftchild;

    if(rightchild<pq->size && pq->pqueue[rightchild]->key > pq->pqueue[largestchild]->key) largestchild = rightchild;

    if(largestchild != i) {
        swap_Element(pq->pqueue,i,largestchild);
        pq_heapify(pq, largestchild);
    }
}


//!  insert a new element in the heap
void pq_insert(priorityQueue* pq, int key, void *payload, int payload_size) {
    if (pq->size == MAX_SIZE) {
        printf("Error: heap is FULL");
        return;
    }
    pq->pqueue[pq->size]=(Element *)malloc(sizeof(Element));
    pq->pqueue[pq->size]->key = key;
    pq->pqueue[pq->size]->payload = malloc(payload_size);
    pq->pqueue[pq->size]->payload_size =  payload_size;
    memcpy(pq->pqueue[pq->size]->payload, payload, payload_size);
    pq->size++;
    
    // reorder the heap from current inserted position till root to maintain the heap order, O(log n)

    int i = pq->size-1;

    while (i>0 && pq->pqueue[i]->key > pq->pqueue[parent(i)]->key) {
        swap_Element(pq->pqueue, i, parent(i));
        i=parent(i);
    }

}


int pq_extract_max(priorityQueue* pq, void *data) {
    assert(pq->size>0);  // nothing to extract
    int max = pq->pqueue[0]->key;
    
    pq->pqueue[0]->key = pq->pqueue[pq->size-1]->key;
    if (data)  memcpy(data, pq->pqueue[pq->size]->payload, pq->pqueue[pq->size]->payload_size);
    pq->size--;
    pq_heapify(pq, 0);
    return max;
}


bool pq_is_empty(priorityQueue* pq) { return pq->size==0; }

void pq_for_each(priorityQueue* pq, iterator h_iterator) {
    assert( h_iterator!=NULL );

    for (int i=0; i<pq->size; i++) h_iterator(pq->pqueue[i]);
}
