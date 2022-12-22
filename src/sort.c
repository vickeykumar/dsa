#include<stdio.h>
#include<stdlib.h>
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
 * O(n2) , best case O(n)
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

/* returns index of the element after partition,
 * such that all the elements left are less then  and all the elements right
 * are greater then the partitioned element 
 */
int partition(int *arr, int low, int high) {
    int ipivot = low;
    int pivot = arr[ipivot];
    for(int i=ipivot+1; i<=high; i++) {
        if (arr[i]<=pivot) {
            ipivot++;
            swap_int(arr, i, ipivot);
        }
    }
    swap_int(arr, ipivot,low);
    return ipivot;
}

/*
 * sorts the array between index low and high
 */
void quick_sort(int *arr, int low, int high) {
    if(low<high) {
        int p = partition(arr, low, high);
        quick_sort(arr, low, p-1);
        quick_sort(arr, p+1, high);
    }
}

void randomized_quick_sort(int *arr, int low, int high) {
    if(low<high) {
        int i=rand()%(high-low+1);
        swap_int(arr, i, low);
        int p = partition(arr, low, high);
        quick_sort(arr, low, p-1);
        quick_sort(arr, p+1, high);
    }
}

/* merge 2 sorted array using in place sorting */
void merge(int *arr, int low, int mid, int high) {
    for (int i=mid; i<=high; i++) {
        int item = arr[i];
        int j=i-1;
        while(j>=low && arr[j]>item) { 
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=item;
        low = j+1;  // with each iteration this low par will keep increasing, as minimum of second array will always be greater than the next j
    }
}

/*
 * sorts the array between index low and high
 */
void merge_sort(int *arr, int low, int high) {
    if(low<high) {
        int mid = (low+high)/2;
        merge_sort(arr, low, mid);
        merge_sort(arr, mid+1, high);
        merge(arr, low, mid, high);
    }
}
