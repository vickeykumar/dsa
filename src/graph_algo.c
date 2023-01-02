#include<stdio.h>
#include<limits.h>
#include<assert.h>
#include "graph_adjm.h"
#include "priorityqueue.h"

bool less_than_weight(void *a, void *b) {
  return *(int*)((Element*)a)->payload < *(int*)((Element*)b)->payload;
}

/*
 * @param arr: adjacency matrix of the graph
 * @param V: number of nodes in graph
 * @param start: start node
 * @returns an array of distance from start node to that node
 */
int* dijkstra(int **arr, int V, int start) {
    Graph *g = createGraph_m(arr, V);
    int *d = (int*)malloc(V*sizeof(int)); // distance array
    // initialize single source
    for (int i=0; i<V; i++) d[i]=INT_MAX;
    d[start]=0;
    
    //priority queue
    priorityQueue* pq = priorityqueue_new(NULL, less_than_weight);
    pq_insert(pq, start, &d[start], sizeof(int));

    while (!pq_is_empty(pq)) {
        int u;
        //printf("pq: ");
        //pq_for_each(pq, display_pq_element);
        u=pq_extract_min(pq, NULL);
        for (int v=0; v<V; v++) {
            int e_w= get_edge(g, u,v);
            if (e_w>0 && d[v] > d[u] + e_w) // relax the edge as v is more reachable via u than other path
            {
                d[v] = d[u] + e_w; // also perform decrease key if already present
                pq_update(pq, v, &d[v], sizeof(int)); /* decrease-key operation(based on the priority key u have set), 
                check less_than_weight, payload is priority here, it will insert in to the pq, if key not found 
                Alternatively pq_insert can also be used */
            }
        }       
    }
    return d;
}

/* Print the prims-MST  in the graph
 * uses dot format, prints ascii or boxart if graph-easy is installed,
 * debian: apt install libgraph-easy-perl 
 */
static void printGraph_MST(Graph* graph, int *parent_mst) {
  char *r_str = NULL;
  char starter[] = "graph G {\n\
\tnode [shape=circle]\n";
  int capacity = strlen(starter);
  r_str = (char*)malloc((capacity+1)*sizeof(char));
  strcpy(r_str, starter);
  strcat(r_str,"\0");
  //printf("%s",r_str);
  for (int i = 0; i < graph->numNodes; i++) {
    char e[100]; 
    for (int j=i; j<graph->numNodes; j++) { // traverse diagonally, as undirected
      if (graph->adjMatrix[i][j]) {
          char *extra=strdup("");
          if (i==parent_mst[j] || j==parent_mst[i]) extra=strdup("color=\"red:blue\"");
          snprintf(e, 100, "\t%d -- %d [label=%d %s];\n",i, j, graph->adjMatrix[i][j], extra);
          capacity += strlen(e);
          r_str = (char*)realloc(r_str, (capacity+1)*sizeof(char));
          assert(r_str!=NULL);
          strcat(r_str, e);
          free(extra);
      }
    }
  }
  r_str = (char*)realloc(r_str, (capacity+3)*sizeof(char));
  assert(r_str!=NULL);
  strcat(r_str, "}\n");
  printf ("Graph: \n\n%s",r_str);
  int cmd_len = strlen(r_str)+50;
  char *cmd = (char*)malloc(cmd_len*sizeof(char));
  snprintf(cmd, cmd_len, "echo \"%s\" | graph-easy -as=boxart", r_str);
  int result = system(cmd);
  if (result != 0) {
    printf("Command failed for graph: ");
  }
  free(r_str);
  free(cmd);
  r_str=NULL;
  cmd=NULL;
}


static void display_pq_element_int(void *data) {
    Element *e = (Element*)data;
    printf("%d -> %p (%d)\n", e->key, e->payload, *(int*)e->payload); // displays pq key and payload
}

/*
 * @param arr: adjacency matrix of the graph
 * @param V: number of nodes in graph
 * @param start: start node
 * @returns an array of parents from start node to that node
 */
int* prims_mst(int **arr, int V, int start) {
    Graph *g = createGraph_m(arr, V);
    int key[V]; // priority key
    int *parent = (int*)malloc(V*sizeof(int)); // array of parents to track MST
    // initialize single source
    for (int i=0; i<V; i++) key[i]=INT_MAX;
    key[start]=0;
    parent[start]=start;    // itself is parent, stopping condition
    //priority queue
    priorityQueue* pq = priorityqueue_new(NULL, less_than_weight);
    pq_insert(pq, start, &key[start], sizeof(int));

    while (!pq_is_empty(pq)) {
        int u;
        //printf("pq: ");
        //pq_for_each(pq, display_pq_element);
        u=pq_extract_min(pq, NULL);
        printf("parent: %d\n",u);
        for (int v=0; v<V; v++) {
            int e_w= get_edge(g, u,v);
            if (e_w>0 && key[v] > e_w) // relax the edge as v is more reachable via u than other path
            {
                printf("relax vertex: %d ew: %d key: %d\n",v, e_w, key[v]);
                key[v] = e_w; // also perform decrease key if already present
                pq_update(pq, v, &key[v], sizeof(int)); /* decrease-key operation(based on the priority key u have set), 
                check less_than_weight, payload is priority here, it will insert in to the pq, if key not found 
                Alternatively pq_insert can also be used */
                pq_for_each(pq, display_pq_element_int);
                parent[v]=u;
            }
        }       
    }
    for (int i = 0; i < V; i++)
        printf("%d - %d\n", parent[i], i);
    printGraph_MST(g, parent);
    return parent;
}
