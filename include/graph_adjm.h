/*
    Graph data structure using ll
*/
#ifndef __DSA_GRAPH_ADJM_H
#define __DSA_GRAPH_ADJM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure to represent a graph
typedef struct Graph {
  int numNodes;
  int** adjMatrix;   // 2d array for graph edges
} Graph;

typedef Graph digraph;

// Create a new graph with n nodes
Graph* createGraph(int n);

// Add an edge from node u to node v, and v to u as it is undirected
void addEdge(Graph* graph, int u, int v);

int* get_adjacent(Graph* graph, int u);

/* Print the adjacency list for each node in the graph
 * uses dot format, prints ascii or boxart if graph-easy is installed,
 * debian: apt install libgraph-easy-perl 
 */
void printGraph(Graph* graph);

// Create a new graph with n nodes
digraph* creatediGraph(int n);

// Add an edge from node u to node v
void addEdge_diGraph(digraph* graph, int u, int v);

int* get_adjacent_digraph(digraph* graph, int u);

/* Print the adjacency list for each node in the graph
 * uses dot format, prints ascii or boxart if graph-easy is installed,
 * debian: apt install libgraph-easy-perl 
 */
void printdiGraph(digraph* graph);

int get_numNodes(digraph* graph);

#endif

