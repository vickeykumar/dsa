#ifndef __DSA_SORT_H
#define __DSA_SORT_H

#include<stdio.h>

extern void selection_sort(int *arr, int low, int high);
/*
 * sorts the array between index low and high
 */
void bubble_sort(int *arr, int low, int high);

/*
 * sorts the array between index low and high
 */
void insertion_sort(int *arr, int low, int high);

/*
 * sorts the array between index low and high
 */
void quick_sort(int *arr, int low, int high);
void randomized_quick_sort(int *arr, int low, int high);

/* merge 2 sorted array using in place sorting */
void merge(int *arr, int low, int mid, int high);

#endif
