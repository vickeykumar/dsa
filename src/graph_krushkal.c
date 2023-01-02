#include<stdio.h>
#include<stdlib.h>
#include "dsf.h"
#include "graph_krushkal.h"

Graph *createGraph_k(int V) {
  Graph *g = (Graph*)malloc(sizeof(Graph));
  g->V = V;
  g->E = 0;
  g->e = NULL;
  return g;
}


void addedge_k(Graph *g, int u, int v) {
    edge e;
    e.u=u;
    e.v=v;
    g->E += 1;
    g->e=(edge*)realloc(g->e, g->E*sizeof(edge));
    g->e[g->E-1]=e;
}

int edge_less_than(const void *e1, const void *e2) {
    return ((edge*)e1)->w - ((edge*)e2)->w;
}

void MST_Kruskal(Graph *g) {  
    edge *result;
    node **set=(node**)calloc(g->V, sizeof(node*)); // array of pointer to node
    for (int i=0; i<g->V; i++) set[i]=makeSet(i);
    qsort(g->e, g->E, sizeof(edge), edge_less_than);

    for (int i=0; i<g->V; i++) {
        if (findSet(set[g->e[i].u]) != findSet(set[g->e[i].v])) {
            printf ("%d--%d(%d)",g->e[i].u, g->e[i].v, g->e[i].w);
            unionSet(set[g->e[i].u], set[g->e[i].v]);
        }
    }
}
