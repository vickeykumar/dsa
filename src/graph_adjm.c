/*
    Graph data structure
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<assert.h>
#include "graph_adjm.h"

// Create a new graph with n nodes
Graph* createGraph(int n) {
  Graph* graph = (Graph*)malloc(sizeof(Graph));
  graph->numNodes = n;
  graph->adjMatrix = (int**)malloc(n*sizeof(int*));
  for (int i = 0; i < n; i++) {
    graph->adjMatrix[i] = (int*)malloc(n*sizeof(int));
    for (int j=0;j<n; j++) graph->adjMatrix[i][j] = 0;
  }
  return graph;
}

// Add an edge from node u to node v, and v to u as it is undirected
void addEdge(Graph* graph, int u, int v) {
  graph->adjMatrix[u][v] = 1;

  // add v to u
  graph->adjMatrix[v][u] = 1;
}

int* get_adjacent(Graph* graph, int u) {
    // iterate and check for non-zero for adjacent nodes
    return graph->adjMatrix[u];
}

/* Print the adjacency list for each node in the graph
 * uses dot format, prints ascii or boxart if graph-easy is installed,
 * debian: apt install libgraph-easy-perl 
 */
void printGraph(Graph* graph) {
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
          snprintf(e, 100, "\t%d -- %d;\n",i, j);
          capacity += strlen(e);
          r_str = (char*)realloc(r_str, (capacity+1)*sizeof(char));
          assert(r_str!=NULL);
          strcat(r_str, e);
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


// Create a new digraph with n nodes
digraph* creatediGraph(int n) {
  digraph* graph = (digraph*)malloc(sizeof(digraph));
  graph->numNodes = n;
  graph->adjMatrix = (int**)malloc(n*sizeof(int*));
  for (int i = 0; i < n; i++) {
    graph->adjMatrix[i] = (int*)malloc(n*sizeof(int));
    for (int j=0;j<n; j++) graph->adjMatrix[i][j] = 0;
  }
  return graph;
}

// Add an edge from node u to node v
void addEdge_diGraph(digraph* graph, int u, int v) {
  graph->adjMatrix[u][v] = 1;

}

// returns iterator to adjacent node
int* get_adjacent_digraph(digraph* digraph, int u) {
    // iterate and check for non-zero for adjacent nodes
    return digraph->adjMatrix[u];
}

int get_numNodes(digraph* graph) {
    return graph->numNodes;
}

/* Print the adjacency list for each node in the graph
 * uses dot format, prints ascii or boxart if graph-easy is installed,
 * debian: apt install libgraph-easy-perl 
 */
void printdiGraph(digraph* graph) {
  char *r_str = NULL;
  char starter[] = "digraph G {\n\
\tnode [shape=circle]\n";
  int capacity = strlen(starter);
  r_str = (char*)malloc((capacity+1)*sizeof(char));
  strcpy(r_str, starter);
  strcat(r_str,"\0");
  //printf("%s",r_str);
  for (int i = 0; i < graph->numNodes; i++) {
    char e[100]; 
    for (int j=0; j<graph->numNodes; j++) {
      if (graph->adjMatrix[i][j]) {
          snprintf(e, 100, "\t%d -> %d;\n",i, j);
          capacity += strlen(e);
          r_str = (char*)realloc(r_str, (capacity+1)*sizeof(char));
          assert(r_str!=NULL);
          strcat(r_str, e);
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
  r_str=NULL;
  free(cmd);
  cmd = NULL;
}





