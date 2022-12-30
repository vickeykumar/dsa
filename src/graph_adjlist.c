/*
    Graph data structure
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<assert.h>
#include "graph_ll.h"

// Create a new node
Node* createNode(int data) {
  Node* newNode = (Node*)malloc(sizeof(Node));
  newNode->data = data;
  newNode->next = NULL;
  return newNode;
}

// Create a new graph with n nodes
Graph* createGraph(int n) {
  Graph* graph = (Graph*)malloc(sizeof(Graph));
  graph->numNodes = n;
  graph->adjList = (Node**)malloc(n * sizeof(Node*));
  for (int i = 0; i < n; i++) {
    graph->adjList[i] = NULL;
  }
  return graph;
}

// Add an edge from node u to node v, and v to u as it is undirected
void addEdge(Graph* graph, int u, int v) {
  Node* newNode = createNode(v);
  newNode->next = graph->adjList[u];
  graph->adjList[u] = newNode;

  // add v to u

  newNode = createNode(u);
  newNode->next = graph->adjList[v];
  graph->adjList[v] = newNode;
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
    Node* curr = graph->adjList[i];
    while (curr != NULL) {
      snprintf(e, 100, "\t%d -- %d;\n",i, curr->data);
      curr = curr->next;
      capacity += strlen(e);
      r_str = (char*)realloc(r_str, (capacity+1)*sizeof(char));
      assert(r_str!=NULL);
      strcat(r_str, e);
    }
  }
  strcat(r_str, "}\n");
  printf ("Graph: \n\n%s",r_str);
  int cmd_len = strlen(r_str)+50;
  char *cmd = (char*)malloc(cmd_len*sizeof(char));
  snprintf(cmd, cmd_len, "echo \"%s\" | graph-easy -as=boxart", r_str);
  int result = system(cmd);
  if (result != 0) {
    printf("Command failed for graph: ");
  }
}




// Create a new digraph with n nodes
digraph* creatediGraph(int n) {
  digraph* graph = (digraph*)malloc(sizeof(digraph));
  graph->numNodes = n;
  graph->adjList = (Node**)malloc(n * sizeof(Node*));
  for (int i = 0; i < n; i++) {
    graph->adjList[i] = NULL;
  }
  return graph;
}

// Add an edge from node u to node v
void addEdge_diGraph(digraph* graph, int u, int v) {
  Node* newNode = createNode(v);
  newNode->next = graph->adjList[u];
  graph->adjList[u] = newNode;

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
    Node* curr = graph->adjList[i];
    while (curr != NULL) {
      snprintf(e, 100, "\t%d -> %d;\n",i, curr->data);
      curr = curr->next;
      capacity += strlen(e);
      r_str = (char*)realloc(r_str, (capacity+1)*sizeof(char));
      assert(r_str!=NULL);
      strcat(r_str, e);
    }
  }
  strcat(r_str, "}\n");
  printf ("Graph: \n\n%s",r_str);
  int cmd_len = strlen(r_str)+50;
  char *cmd = (char*)malloc(cmd_len*sizeof(char));
  snprintf(cmd, cmd_len, "echo \"%s\" | graph-easy -as=boxart", r_str);
  int result = system(cmd);
  if (result != 0) {
    printf("Command failed for graph: ");
  }
}
