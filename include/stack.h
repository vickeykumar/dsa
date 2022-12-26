#ifndef __DSA_STACK_H
#define __DSA_STACK_H

#include "common.h"
#include "llist.h"

typedef struct {
  llist *list;
} stack;

void stack_new(stack *s, int elementSize, freeFunction freeFn);

void stack_destroy(stack *s);

void stack_push(stack *s, void *element);

/* sets data after pop */
void stack_pop(stack *s, void *data);

/* peeks and copies data without poping the stack */
void stack_peek(stack *s, void *data);

int stack_size(stack *s);

bool stack_isEmpty(stack *s);
/*
iterate over all the elements of the stack using the iterate function, 
that recieves the data as void ptr(needs typecast to desired datatype.)
*/
void stack_for_each(stack *s, iterator ll_iterator);

#endif

