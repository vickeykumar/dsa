#ifndef __DSA_SEARCH_H
#define __DSA_SEARCH_H

/*
 * return index of the item if present,
 * else returns -1
 */
int LinearSearch(int *arr, int size, int item);

/*
 * return index of the item if present,
 * else returns -1
 * Note: assume array is sorted
 */
extern int BinarySearch(int *arr, int size, int item);

#endif
