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

void display_pq_element(void *data) {
    Element *e = (Element*)data;
    printf("%d -> %p\n", e->key, e->payload); // displays pq key and payload
}

priorityQueue* priorityqueue_new(freeFunction freeFn, Comparater comp) {
    priorityQueue* pq = (priorityQueue*)malloc(sizeof(priorityQueue));
    pq->size = 0;
    pq->freeFn=freeFn;
    if (comp)
        pq->compare = comp;
    else
        pq->compare = greater_than_int; // default max heap, first field of element is key so type cast will return key for comparision
    
    return pq;
}

// Function to initialize the heap
void pq_init(priorityQueue* pq, freeFunction freeFn, Comparater comp) {
  pq->size = 0;
  pq->freeFn = freeFn;
  if (comp)
        pq->compare = comp;
    else
        pq->compare = greater_than_int; // default MAX heap
}


void pq_delete(priorityQueue* pq) {
    while (pq->freeFn && pq->size>0) {
        if (pq->pqueue[pq->size]->payload)
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
    if(leftchild<pq->size && pq->compare(pq->pqueue[leftchild], pq->pqueue[i])) largestchild = leftchild;

    if(rightchild<pq->size && pq->compare(pq->pqueue[rightchild], pq->pqueue[largestchild])) largestchild = rightchild;

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
    if (payload) {
        pq->pqueue[pq->size]->payload = malloc(payload_size);
        pq->pqueue[pq->size]->payload_size =  payload_size;
        memcpy(pq->pqueue[pq->size]->payload, payload, payload_size);
    }
    pq->size++;
    
    // reorder the heap from current inserted position till root to maintain the heap order, O(log n)

    int i = pq->size-1;

    while (i>0 && pq->compare(pq->pqueue[i], pq->pqueue[parent(i)])) {
        swap_Element(pq->pqueue, i, parent(i));
        i=parent(i);
    }

}

// update the data to the pq, will behave like normal increase key or decrease key for respective pq
void pq_update(priorityQueue* pq, int key, void *payload, int payload_size) {
    // first find the key element
    int i = pq->size-1;
    // loop till key is not found in pq
    while (i>0 && pq->pqueue[i]->key != key ) {
        i=parent(i);
    }
    if (i<0 || (i==0 && pq->pqueue[i]->key != key)) {
        //still key not found, even at root level, just insert the new key and return
        pq_insert(pq, key, payload, payload_size);
        return;
    }
    printf("%d key found at: %d\n",key,i); 
    // key is found, just update the payload, assuming payload is already allocated by previous insert.
    // TBD. free and realloc in case of new size
    // create a temp dummy Element for comparision, lets say decrease key for min priority que and 
    // increase key for max priority queue, do nothing if comparision is not satisfied.
    Element e;
    e.key=key;
    e.payload=payload;
    e.payload_size = payload_size;
    if (payload && pq->compare(&e, pq->pqueue[i])) {
        memcpy(pq->pqueue[i]->payload, payload, payload_size);
    }

    // now, reorder the heap from current update position till root to maintain the heap order, O(log n)

    while (i>0 && pq->compare(pq->pqueue[i], pq->pqueue[parent(i)])) {
        swap_Element(pq->pqueue, i, parent(i));
        i=parent(i);
    }
}

int pq_extract_max(priorityQueue* pq, void *data) {
    assert(pq->size>0);  // nothing to extract
    int max = pq->pqueue[0]->key;
    
    pq->pqueue[0]->key = pq->pqueue[pq->size-1]->key;
    if (data && pq->pqueue[0]->payload )  memcpy(data, pq->pqueue[0]->payload, pq->pqueue[0]->payload_size);
    // copy last payload as well to top location
    if (pq->pqueue[pq->size-1]->payload) memcpy(pq->pqueue[0]->payload, pq->pqueue[pq->size-1]->payload, pq->pqueue[pq->size-1]->payload_size);
    else pq->pqueue[0]->payload = NULL;
    pq->size--;
    pq_heapify(pq, 0);
    return max;
}

int pq_extract_min(priorityQueue* pq, void *data) {
    assert(pq->size>0);  // nothing to extract
    int min = pq->pqueue[0]->key;

    pq->pqueue[0]->key = pq->pqueue[pq->size-1]->key;
    if (data && pq->pqueue[0]->payload )  memcpy(data, pq->pqueue[0]->payload, pq->pqueue[0]->payload_size);
    // copy last payload as well to top location
    if (pq->pqueue[pq->size-1]->payload) memcpy(pq->pqueue[0]->payload, pq->pqueue[pq->size-1]->payload, pq->pqueue[pq->size-1]->payload_size);
    else pq->pqueue[0]->payload = NULL;
    pq->size--;
    pq_heapify(pq, 0);
    return min;
}


bool pq_is_empty(priorityQueue* pq) { return pq->size==0; }

void pq_for_each(priorityQueue* pq, iterator h_iterator) {
    assert( h_iterator!=NULL );

    for (int i=0; i<pq->size; i++) h_iterator(pq->pqueue[i]);
}
