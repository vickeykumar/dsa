#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include "queue.h"

void queue_new(queue *q, int dataSize, freeFunction freeFn) {
    if (!q) q=(queue*)malloc(sizeof(queue));
    q->list = (llist*)malloc(sizeof(llist));
    llist_new(q->list, dataSize, freeFn);
}

void queue_destroy(queue *q) {
    llist_destroy(q->list);
    free(q->list);
    q->list=NULL;
}

void queue_enque(queue *q, void *data) { llist_append(q->list, data); }

/* sets data after dequeue operation  */
void queue_deque(queue *q, void *data) { assert(queue_size(q)>0); llist_head(q->list, data, true); }

/* peeks and copies data without dequeue from Rear end */
void queue_peek(queue *q, void *data) { assert(queue_size(q)>0); llist_head(q->list, data, false); }

int queue_size(queue *q) { return llist_size(q->list); }

bool queue_isEmpty(queue *q) {return (queue_size(q) == 0); }
/*
iterate over all the elements of the queue using the iterate function, 
that recieves the data as void ptr(needs typecast to desired datatype.)
*/
void queue_for_each(queue *q, iterator ll_iterator) {
    llist_for_each(q->list, ll_iterator);
}

