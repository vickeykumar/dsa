#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include "common.h"
#include "llist.h"
#include "stack.h"

void stack_new(stack *s, int dataSize, freeFunction freeFn) {
    s->list = (llist*)malloc(sizeof(llist));
    llist_new(s->list, dataSize, freeFn);
}

void stack_destroy(stack *s) {
    llist_destroy(s->list);
    free(s->list);
}

/*
 * pushing to head of ll, so that pop can be O(1)
*/
void stack_push(stack *s, void *data) {
    llist_prepend(s->list, data);
}

/* stack pop O(1) */

void stack_pop(stack *s, void *data) {
    assert(stack_size(s) > 0);
    llist_head(s->list, data, true); 
}
/* stack peek O(1) */
void stack_peek(stack *s, void *data) {
    assert(stack_size(s) > 0);
    llist_head(s->list, data, false);
}

int stack_size(stack *s) { return llist_size(s->list); }

/*
iterate over all the elements of the stack using the iterate function, 
that recieves the data as void ptr(needs typecast to desired datatype.)
*/
void stack_for_each(stack *s, iterator ll_iterator) {
    llist_for_each(s->list, ll_iterator);
}
