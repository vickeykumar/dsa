#include "../include/common.h"
#include<stdio.h>

void display_int(void *data) {
    int *i=(int*)data;
    printf("%d ", *i);    
}
