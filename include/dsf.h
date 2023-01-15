#ifndef __DSA_DSF_H
#define __DSA_DSF_H
/*
 * disjoint set forest Data setructure
 * Applications: 
 * 1. merge accounts with the same email id - email id can be the key for this data structure
 *          - https://leetcode.com/problems/accounts-merge/description/
 * 2.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// a node in the disjoint-set forest
typedef struct node {
  int data;
  int rank;
  struct node *parent;
} node;


// create a new set with element x, x as parent
node *makeSet(int x);

// finds the root of the set that element x belongs to
node *findSet(node *x);

// merges the set containing element x with the set containing element y
void unionSet(node *x, node *y);

#endif
