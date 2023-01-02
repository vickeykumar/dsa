/**
 * adata structure to implement a disjoint set forest
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dsf.h"


// create a new set with element x, x as parent
node *makeSet(int x) {
  node *n = (node*)malloc(sizeof(node));
  n->data = x;
  n->rank = 0;
  n->parent = n;
  return n;
}

// finds the root of the set that element x belongs to
node *findSet(node *x) {
  if (x != x->parent) {
    x->parent = findSet(x->parent);
  }
  return x->parent;
}

// merges the set containing element x with the set containing element y
void unionSet(node *x, node *y) {
  node *root1 = findSet(x);
  node *root2 = findSet(y);
  // node with more height becomes parent to balance height
  if (root1 != root2) {
    if (root1->rank < root2->rank) {
      root1->parent = root2;
    } else if (root1->rank > root2->rank) {
      root2->parent = root1;
    } else {    // increase the rank whenever height increases
      root2->parent = root1;
      root1->rank++;
    }
  }
}

