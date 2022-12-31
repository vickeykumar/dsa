#ifndef __DSA_QUEUE_H
#define __DSA_QUEUE_H

#include "common.h"
#include "llist.h"

typedef struct {
  llist *list;
} queue;

void queue_new(queue *q, int dataSize, freeFunction freeFn);

void queue_destroy(queue *q);

void queue_enque(queue *q, void *data);

/* sets data after dequeue operation  */
void queue_deque(queue *q, void *data);

/* peeks and copies data without dequeue from Rear end */
void queue_peek(queue *q, void *data);

int queue_size(queue *q);

bool queue_isEmpty(queue *q);
/*
iterate over all the elements of the queue using the iterate function, 
that recieves the data as void ptr(needs typecast to desired datatype.)
*/
void queue_for_each(queue *q, iterator ll_iterator);

#endif

