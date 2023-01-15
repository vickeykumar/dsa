#include "vector.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

static void vector_grow(vector *vector) {
  vector->allocatedLength *= 2;
  vector->elements =
      realloc(vector->elements, vector->elementSize * vector->allocatedLength);
  assert(vector->elements);
}

static void *vector_address(vector *vector, int index) {
  int addr = vector->elementSize * index;
  return (char *)vector->elements + addr;
}

static void vector_copy_item(vector *vector, int destIndex, int sourceIndex) {
  void *source = vector_address(vector, sourceIndex);
  void *target = vector_address(vector, destIndex);
  memcpy(target, source, vector->elementSize);
}

vector* vector_new(int elementSize, freeFunction freeFn) {
  assert(elementSize > 0);
  vector *v=(vector*)malloc(sizeof(vector));

  v->elementSize = elementSize;
  v->logicalLength = 0;
  v->allocatedLength = 2;
  v->elements = NULL;
  v->freeFn = freeFn;
  vector_grow(v);
  return v;
}

void vector_init(vector *v, int elementSize, freeFunction freeFn) {
  if (v->elementSize) return;   // inited before already
  assert(elementSize > 0);
  v->elementSize = elementSize;
  v->logicalLength = 0;
  v->allocatedLength = 2;
  v->elements = NULL;
  v->freeFn = freeFn;
  vector_grow(v);
}

void vector_destroy(vector *vector) {
  if (vector->freeFn) {
    int i;
    for (i = 0; i < vector_size(vector); i++) {
      vector->freeFn(vector_address(vector, i));
    }
  }

  // free main elements
  free(vector->elements);
  vector->elements=NULL;
  vector->elementSize=0;
  vector->logicalLength = 0;
}

int vector_size(vector *vector) { return vector->logicalLength; }

void vector_push_back(vector *vector, void *element) {
  if (vector->allocatedLength == vector->logicalLength) {
    vector_grow(vector);
  }

  void *target = vector_address(vector, vector->logicalLength++);
  memcpy(target, element, vector->elementSize);
}

void vector_item_at(vector *vector, int index, void *target) {
  assert(index >= 0 && index < vector->logicalLength);

  void *source = vector_address(vector, index);
  memcpy(target, source, vector->elementSize);
}

void vector_insert_at(vector *vector, int index, void *target) {
  assert(index >= 0 && index <= vector->logicalLength);
  vector_push_back(vector, target);

  if (index < vector->logicalLength) {
    int i;
    void *source;
    void *destination;

    for (i = vector->logicalLength - 2; i > index; i--) {
      source = vector_address(vector, i);
      destination = vector_address(vector, i + 1);
      memcpy(destination, source, vector->elementSize);
    }

    destination = vector_address(vector, i);
    memcpy(destination, target, vector->elementSize);
  }
}

void vector_remove_at(vector *vector, int index) {
  assert(index >= 0 && index < vector->logicalLength);

  // remove the item
  void *item = vector_address(vector, index);
  if (vector->freeFn) {
    vector->freeFn(item);
  }

  while (++index < vector->logicalLength) {
    vector_copy_item(vector, index - 1, index);
  }

  vector->logicalLength--;
}

void vector_pop_back(vector *vector) {
    vector_remove_at(vector, vector->logicalLength-1);
}

vector* vector_copy(vector *vect) {
    vector *v1 = vector_new(vect->elementSize, vect->freeFn);
    for (int i = 0; i < vector_size(vect); i++) {
      vector_push_back(v1, vector_address(vect, i));
    }
    return v1;
}

/*
iterate over all the elements of the vector using the iterate function, 
that recieves the data as void ptr(needs typecast to desired datatype.)
*/
void vector_for_each(vector *vector, iterator v_iterator) {
    assert(v_iterator != NULL);
    for (int i = 0; i < vector_size(vector); i++) {
      v_iterator(vector_address(vector, i));
    }    
}

