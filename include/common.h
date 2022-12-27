#ifndef __DSA_COMMON_H
#define __DSA_COMMON_H

#include <stdint.h>

typedef uint32_t ds_size_t;
typedef void (*freeFunction)(void *);
typedef ds_size_t (*hashFunction)(const void* key, int keySize, ds_size_t seed);

typedef void (*iterator)(void *);
void display_int(void *data);
void swap_int(int *arr, int i, int j);

#endif
