#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include "common.h"
#include "hashmap.h"
#include "Hashes.h"

/*Create a New hashmap*/
hashmap* hashmap_new(ds_size_t capacity, ds_size_t seed, hashFunction hashFn, freeFunction freeFn) {
    hashmap *m = (hashmap*)malloc(sizeof(hashmap));
    m->capacity = capacity;
    m->seed = seed;
    if (!hashFn) hashFn=MurmurOAAT; //default hashing murmur
    m->hashFn = hashFn;
    m->freeFn = freeFn;
    m->nodearr = (hashNode**)calloc(capacity, sizeof(hashNode*)); // calloc, why?, array of hashnode pointers
    return m;
}

/* insert in to hashmap after calculating the hash */
void hashmap_insert(hashmap *m, const char *key, const void *data, ds_size_t data_size) {
    ds_size_t hash = m->hashFn(key, strlen(key), m->seed)%m->capacity;
    ds_size_t slot=hash;
    //printf("slot:%d, key: %s", slot, key);
    int i=0;
    while (i<m->capacity && m->nodearr[slot]) {
        slot=(slot+1)%m->capacity; //open addressing
        i++;
        if(i==m->capacity) break;   // traversed all the slots
    }
    //printf("slot:%d, key: %s", slot, key);
    m->nodearr[slot] = (hashNode*)malloc(sizeof(hashNode));
    m->nodearr[slot]->key = strdup(key);
    m->nodearr[slot]->data = malloc(sizeof(data_size));
    memcpy(m->nodearr[slot]->data, data, data_size); 
    m->nodearr[slot]->data_size = data_size;
} 

void delete_slot(hashmap *m, const char *key, ds_size_t slot) {
    if(slot<m->capacity && m->nodearr[slot] && (strcmp(m->nodearr[slot]->key, key)==0)) {
        if (m->freeFn) m->freeFn(m->nodearr[slot]->data);
        free(m->nodearr[slot]->key);
        free(m->nodearr[slot]);;
        m->nodearr[slot]=NULL;
    }
}

/* delete from hashmap , openaddressing with linear probing*/
void hashmap_delete(hashmap *m, const char *key) {
    ds_size_t slot = (ds_size_t)hashmap_find(m, key, NULL);
    delete_slot(m, key, slot);

    // now do the linear probing, update the next slots that are probed earlier.
    int i=0;
    slot = (slot + 1) % m->capacity; // back probe till we find NULL, possibility is that location was probed
    while (m->nodearr[slot] != NULL) {
        const char *tmpkey = m->nodearr[slot]->key;
        void *data = m->nodearr[slot]->data;
        ds_size_t data_size = m->nodearr[slot]->data_size;
        delete_slot(m, tmpkey, slot);
        hashmap_insert(m, tmpkey, data, data_size);
        slot = (slot + 1) % m->capacity;
        i++;
        if(i==m->capacity) break;

    }
}

/* find and assign the data repective to the given key frm hashmap
   returns slot if found, else return -1
*/
int hashmap_find(hashmap *m, const char *key, void *data) {
    ds_size_t hash = m->hashFn(key, strlen(key), m->seed)%m->capacity;
    ds_size_t slot=hash;
    //printf("hash: %d",hash);
    if (!m->nodearr[slot]) return -1;
    int i=0;
    while (m->nodearr[slot] && strcmp(m->nodearr[slot]->key, key) != 0) {
        slot = (slot+1)%m->capacity; //open addressing
        i++;
        if(i==m->capacity) return -1;   // didn't find anything yet
    }
    if(data) memcpy(data, m->nodearr[slot]->data, m->nodearr[slot]->data_size);
    return (int)slot;
}

/*
iterate over all the elements of the hashmap using the iterate function, 
that recieves the data as void ptr(needs typecast to desired datatype.)
*/
void hashmap_for_each(hashmap *m, iterator ll_iterator) {
    assert(ll_iterator != NULL);
    int slot=0;
    while(slot<m->capacity) {
        if(m->nodearr[slot]) {
            printf("slot %d : %s->",slot,m->nodearr[slot]->key);
            ll_iterator(m->nodearr[slot]->data);
        } else {
            printf("slot %d : NULL->NULL ",slot);
        }
        printf("\n");
        slot++;
    }
}

