#include<stdio.h>
#include "../include/sort.h"

void swap_int(int *arr, int i, int j) {
    int tmp=arr[i];
    arr[i]=arr[j];
    arr[j]=tmp;
}

/*
 * sorts the array between index low and high
 */
void selection_sort(int *arr, int low, int high) {
    for (int i=low; i<=high; i++) {
        int min=i;
        for(int j=i+1;j<=high;j++) {
            if(arr[j]<arr[min]) min=j;
        }
        swap_int(arr, i, min);
    }
}

/*
 * sorts the array between index low and high
 */
void bubble_sort(int *arr, int low, int high) {
    for (int i=low; i<=high-1; i++) {
        for(int j=low;j<=high-i-1;j++) {
            if(arr[j]>arr[j+1]) swap_int(arr, j, j+1);
        }
    }
}

/*
 * sorts the array between index low and high
 */
void insertion_sort(int *arr, int low, int high) {
    for (int i=low; i<high; i++) {
        int item = arr[i+1];
        int j=i;
        while(j>=low && arr[j]>item) {
             arr[j+1]=arr[j];
             j--;
        }
        arr[j+1]=item;
    }
}
