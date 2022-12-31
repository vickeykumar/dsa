#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "stack.h"
#include "../include/queue.h"
#include "graph_traversal.h"

// push-> pop,visit,push(nighbors)
void dfs(Graph *g, int start) {
    stack s;
    stack_new(&s, sizeof(int), NULL);
    stack_push(&s, &start);
    bool *visited = (bool*)calloc(g->numNodes, sizeof(bool));
    visited[start] = true;
    while (! stack_isEmpty(&s)) {
        int u;
        stack_pop(&s, &u);
        if (!visited[u]) visited[u] = true;
        printf("%d ",u);
        int *adj_nodes = get_adjacent_digraph(g, u);

        for (int v=0;v < get_numNodes(g); v++) {
            if (adj_nodes[v] && !visited[v]) {
                stack_push(&s, &v);
            }
        } 
    } 
}

// enque, deque, enque and visit adjacent nodes as we go
void bfs(Graph *g, int start) {
  // Queue for storing the vertices to visit
  queue q;
  queue_new(&q, sizeof(int), NULL);
  queue_enque(&q, &start);
  bool *visited = (bool*)calloc(g->numNodes, sizeof(bool));
  // Mark the current vertex as visited and add it to the queue
  visited[start] = true;

  while (! queue_isEmpty(&q)) {
        int u;
        queue_deque(&q, &u);
        printf("%d ",u);
        int *adj_nodes = get_adjacent_digraph(g, u);

        for (int v=0;v < get_numNodes(g); v++) {
            if (adj_nodes[v] && !visited[v]) {
                queue_enque(&q, &v);
                visited[v] = true;
            }
        } 
    }

}
