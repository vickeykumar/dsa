#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include "heapsort.h"

MaxHeap* maxheap_new() {
    MaxHeap *h = (MaxHeap*)malloc(sizeof(MaxHeap));
    h->size = 0;
    return h;
}

// Function to initialize the heap
void init(MaxHeap* heap) {
  heap->size = 0;
}


void maxheap_delete(MaxHeap *h) {
    if(h) free(h);
    h=NULL;
}
int parent(int i) { return (i-1)/2; }

//! left child of i
int left(int i) { return 2*i+1; }

//! right child of i
int right(int i) { return 2*i+2; }

//! maintain heap property at i
void max_heapify(MaxHeap* h, int i) {
    int largestchild =i;
    int leftchild = left(i);
    int rightchild = right(i);

    //! find largest childs index
    if(leftchild<h->size && h->heap[leftchild]>h->heap[i]) largestchild = leftchild;

    if(rightchild<h->size && h->heap[rightchild]>h->heap[largestchild]) largestchild = rightchild;

    if(largestchild != i) {
        swap_int(h->heap,i,largestchild);
        max_heapify(h, largestchild);
    }
}


//!  insert a new element in the heap
void heap_insert(MaxHeap* h, int value) {
    if (h->size == MAX_SIZE) {
        printf("Error: heap is FULL");
        return;
    }
    h->heap[h->size]=value;
    h->size++;
    
    // reorder the heap from current inserted position till root to maintain the heap order, O(log n)

    int i = h->size-1;

    while (i>0 && h->heap[i]>h->heap[parent(i)]) {
        swap_int(h->heap, i, parent(i));
        i=parent(i);
    }

}


int extract_max(MaxHeap *h) {
    assert(h->size>0);  // nothing to extract
    int max = h->heap[0];
    
    h->heap[0]=h->heap[h->size-1];

    h->size--;
    max_heapify(h, 0);
    return max;
}


bool is_empty(MaxHeap *h) { return h->size==0; }

// Function to sort an array in ascending order using the heap sort algorithm
void heap_sort(int* array, int size) {
  MaxHeap *heap = maxheap_new();
  // Insert the elements of the array into the heap
  for (int i = 0; i < size; i++) {
    heap_insert(heap, array[i]);
  }
  // Extract the elements from the heap in descending order
  for (int i = size - 1; i >= 0; i--) {
    array[i] = extract_max(heap);
  }
}


void heap_for_each(MaxHeap* h, iterator h_iterator) {
    assert( h_iterator!=NULL );

    for (int i=0; i<h->size; i++) h_iterator(&h->heap[i]);
}
