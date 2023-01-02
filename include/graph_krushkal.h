#ifndef __DSA_KRUSHKAL_H
#define __DSA_KRUSHKAL_H

#include<stdio.h>
#include<stdlib.h>
#include "dsf.h"

typedef struct {
    int u,v;
    int w;  // weight of the edge
} edge;

typedef struct {
    int V,E;
    edge *e;    // array of edges
} Graph;

Graph *createGraph_k(int V);

void addedge_k(Graph *g, int u, int v);

int edge_less_than(const void *e1, const void *e2);
void MST_Kruskal(Graph *g); 

#endif
