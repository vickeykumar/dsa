#ifndef __DSA_HEAPSORT_H
#define __DSA_HEAPSORT_H

#include<stdio.h>
#include<stdlib.h>
#include "common.h"

#define MAX_SIZE 1024

typedef struct {
    int size;
    int heap[MAX_SIZE];
} MaxHeap;

MaxHeap* maxheap_new();

void maxheap_delete(MaxHeap *h);
int parent(int i);

//! left child of i
int left(int i);

//! right child of i
int right(int i);

//! maintain heap property at i
void max_heapify(MaxHeap* h, int i);


//!  insert a new element in the heap
void heap_insert(MaxHeap* h, int value);


int extract_max(MaxHeap *h);

bool is_empty(MaxHeap *h);

//! Function to sort an array in ascending order using the heap sort algorithm
void heap_sort(int* array, int size);

void heap_for_each(MaxHeap* h, iterator h_iterator);

#endif

