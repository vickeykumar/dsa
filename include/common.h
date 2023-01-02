#ifndef __DSA_COMMON_H
#define __DSA_COMMON_H

#include <stdint.h>
#include<limits.h>

#define MAX_COUNT 100

typedef uint32_t ds_size_t;
typedef void (*freeFunction)(void *);
typedef ds_size_t (*hashFunction)(const void* key, int keySize, ds_size_t seed);

typedef void (*iterator)(void *);
void display_int(void *data);
void swap_int(int *arr, int i, int j);
typedef bool (*Comparater)(void* a, void* b);
bool less_than_int(void* a, void* b);
bool greater_than_int(void* a, void* b);

/*
 *assuming caller will free the memory return matrix in pointer to array of rows fmt
 * @param matrix, 2d array of size m*n, where m is number of rows
 */
int** getmatrix_ptr(int matrix[][MAX_COUNT], int m);

void display_int_arr(int *arr, int n);

#endif
