#ifndef __DSA_RECURSION_H
#define __DSA_RECURSION_H

#include "vector.h"

void display_vector(void *data);
// returns a vector of result vectors
vector* powerset(int *arr, int pos, int size);

// returns a vector of permutations
void permute(char *arr, int pos, vector *v);

void permute2(char *arr, int pos, vector *v);
#endif
