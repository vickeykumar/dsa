#include<stdio.h>
#include "search.h"

int LinearSearch(int *arr, int size, int item)
{
    for ( int i=0; i<size; i++) {
        if (arr[i]==item) return i;
    } 
    return -1;
}

int BinarySearch(int *arr, int size, int item)
{
    int beg=0, end=size-1;
    while (beg<=end) {
        int mid=(beg+end)/2;
        if (arr[mid]<item) beg=mid+1;
        else if (arr[mid]>item) end=mid-1;
        else return mid;
    }
    return -1;
}
