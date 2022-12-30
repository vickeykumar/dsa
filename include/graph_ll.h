/*
    Graph data structure using ll
*/
#ifndef __DSA_GRAPH_LL_H
#define __DSA_GRAPH_LL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure to represent a node in the graph
typedef struct Node {
  int data;
  struct Node* next;
} Node;

// Define a structure to represent a graph
typedef struct Graph {
  int numNodes;
  Node** adjList;   // array of adjacency lists of graph nodes
} Graph;

// Create a new node
Node* createNode(int data);

// Create a new graph with n nodes
Graph* createGraph(int n);

// Add an edge from node u to node v, and v to u as it is undirected
void addEdge(Graph* graph, int u, int v);

/* Print the adjacency list for each node in the graph
 * uses dot format, prints ascii or boxart if graph-easy is installed,
 * debian: apt install libgraph-easy-perl 
 */
void printGraph(Graph* graph);


// Define a structure to represent a digraph
typedef struct {
  int numNodes;
  Node** adjList;   // array of adjacency lists of digraph nodes
} digraph;

// Create a new graph with n nodes
digraph* creatediGraph(int n);

// Add an edge from node u to node v
void addEdge_diGraph(digraph* graph, int u, int v);

/* Print the adjacency list for each node in the graph
 * uses dot format, prints ascii or boxart if graph-easy is installed,
 * debian: apt install libgraph-easy-perl 
 */
void printdiGraph(digraph* graph);

#endif

