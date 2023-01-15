#include "../include/common.h"
#include<stdlib.h>
#include<stdio.h>
#include<limits.h>
#include<string.h>


void display_int(void *data) {
    int *i=(int*)data;
    printf("%d ", *i);    
}

void display_string(void *data) {
    char *s=(char*)data;
    printf("%s ", s);
}

bool less_than_int(void *a, void *b) {
  return *(int*)a < *(int*)b;
}

bool greater_than_int(void *a, void *b) {
  return *(int*)a > *(int*)b;
}

/*
 *assuming caller will free the memory return matrix in pointer to array of rows fmt
 * @param matrix, 2d array of size m*n, where m is number of rows
 */
int** getmatrix_ptr(int matrix[][MAX_COUNT], int m) {
    int** mat=(int**)malloc(m*sizeof(int*));
    for (int i =0; i<m; i++) mat[i]=matrix[i];
    return mat;
}

void display_int_arr(int *arr, int n) {
    for (int i=0; i<n; i++)
        printf("%d ", arr[i]);
}


int* intptr(const int idata) {
    int d=idata;
    int *ptr;
    memcpy(ptr,&d, sizeof(int));
    return ptr;
}

void swap_int(int *arr, int i, int j) {
    int tmp=arr[i];
    arr[i]=arr[j];
    arr[j]=tmp;
}

void swap_char(char *arr, int i, int j) {
    char tmp=arr[i];
    arr[i]=arr[j];
    arr[j]=tmp;
}
