#ifndef __DSA_GRAPH_ALGO_H
#define __DSA_GRAPH_ALGO_H

#include<stdio.h>
#include<limits.h>
#include "graph_adjm.h"
#include "priorityqueue.h"

/*
 * @param arr: adjacency matrix of the graph
 * @param V: number of nodes in graph
 * @param start: start node
 * @returns an array of distance from start node to that node
 */
int* dijkstra(int **arr, int V, int start);


/*
 * @param arr: adjacency matrix of the graph
 * @param V: number of nodes in graph
 * @param start: start node
 * @returns an array of parents from start node to that node
 */
int* prims_mst(int **arr, int V, int start);

#endif
