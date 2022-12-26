#ifndef __DSA_HASHMAP_H
#define __DSA_HASHMAP_H

#include "common.h"
#define MIN_HASH_SIZE 1024

typedef struct __hashnode {
    char* key;
    void* data;
    ds_size_t data_size;
} hashNode;

// array of hashnodes is hashmap
typedef struct _hashmap {
    hashNode **nodearr;
    ds_size_t capacity;
    ds_size_t seed;
    hashFunction hashFn;
    freeFunction freeFn;
} hashmap;

/*Create a New hashmap*/
hashmap* hashmap_new(ds_size_t capacity, ds_size_t seed, 
                        hashFunction hashFn,
                        freeFunction freeFn);

/* insert in to hashmap after calculating the hash */
void hashmap_insert(hashmap* m, const char *key, const void *data, ds_size_t data_size);

/* delete from hashmap */
void hashmap_delete(hashmap* m, const char *key);

/* find and assign the data repective to the given key frm hashmap,
   returns index
*/
int hashmap_find(hashmap* m, const char *key, void *data);

void hashmap_for_each(hashmap *m, iterator ll_iterator);

#endif
