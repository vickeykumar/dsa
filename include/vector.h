#ifndef __DSA_VECTOR_H
#define __DSA_VECTOR_H

#include "common.h"

typedef struct {
  void *elements;
  int elementSize;
  int allocatedLength;
  int logicalLength;
  freeFunction freeFn;
} vector;

vector* vector_new(int elementSize, freeFunction freeFn);
void vector_init(vector *v, int elementSize, freeFunction freeFn);
void vector_destroy(vector *vector);

int vector_size(vector *vector);

void vector_push_back(vector *vector, void *element);
void vector_pop_back(vector *vector);

void vector_item_at(vector *vector, int index, void *target);

void vector_insert_at(vector *vector, int index, void *target);

void vector_erase_at(vector *vector, int index);
vector* vector_copy(vector *vector);
void vector_for_each(vector *vector, iterator v_iterator);
#endif
