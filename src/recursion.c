/*
 * few points to note: dont jump to final solution in first shot
 * first find the recurrence, try to print the smaller part of solution
 *
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "recursion.h"

void display_vector(void *data) {
    vector *v = (vector*)data;
    if ( vector_size(v) ==0) printf ("{}");
    else
        vector_for_each(v, display_int);
    printf("\n");
}

// returns a vector of result vectors
vector* powerset(int *arr, int pos, int size) { // print powerset given powerset from pos+1..end
    printf("pos: %d\n",pos);
    vector *result_vector;
    // base case, when pos>=size-1
    if(pos>=size-1) {
        printf("base case: %d\n",pos);
        // allocate the new vector for base case
        result_vector = vector_new(sizeof(vector), NULL);
        vector *v = vector_new(sizeof(int),NULL);
        vector_push_back(result_vector, v); // push empty vector
        v=vector_new(sizeof(int), NULL);
        vector_push_back(v, &arr[pos]);
        vector_push_back(result_vector, v);
        return result_vector;
    }

    vector *previous_result_vector = powerset(arr, pos+1, size); // print powerset given powerset from pos+1..end
    int l = vector_size(previous_result_vector);
    printf("apos: %d l:%d\n",pos,l);
    vector_for_each(previous_result_vector, display_vector);
    for (int i=0; i<l; i++) {
        vector v;
        vector_item_at(previous_result_vector, i, &v);
        vector *cv = vector_copy(&v);// deep copy
        vector_push_back(cv,&arr[pos]);
        printf("cv:i:%d sz:%d\n",i, vector_size(cv));
        vector_for_each(cv, display_int);
        vector_push_back(previous_result_vector, cv); // a vector without cv, current pos is already there in prev_result_vector
    }

    printf("done apos: %d size:%d\n",pos, vector_size(previous_result_vector));
    vector_for_each(previous_result_vector, display_vector);
    result_vector = previous_result_vector;
   return result_vector; // return the final result vector 
}


// returns a vector of permutations, assuming user will free the vector memory 
void permute(char *arr, int pos, vector *result_vector) {
    vector_init(result_vector, sizeof(arr), NULL);
    int size = strlen(arr);
    // base case, when pos == size-1
    if(pos==size-1) {
        // save pemuted results here
        printf("%s\n",arr);
        vector_push_back(result_vector, arr);
        return;
    }
    for (int i=pos; i<size; i++) {
       swap_char(arr, pos, i);
       permute(arr, pos+1, result_vector); // permute rest of the subarray, assuming prefixes are already permuted
       swap_char(arr, pos,i);   // backtracking, undoing the change we have done earlier
    }
}


// lookup , and insert if char not found
static bool lookup_and_insert(char *s, char c) {
    int i=0;
    for (i=0; i<strlen(s); i++)
        if (s[i]==c) return true;
    // not found, insert
    s[i]=c;
    return false;

}

// returns a vector of permutations, assuming user will free the vector memory
// ignores the ocurrences of a character multiple times, n!/r!
void permute2(char *arr, int pos, vector *result_vector) {
    vector_init(result_vector, sizeof(arr), NULL);
    int size = strlen(arr);
    char *set=(char*)calloc(size-pos, sizeof(char)); //set array of char
    //printf("fix at pos: %d, size:%d\n",pos,size);
    // base case, when pos == size-1
    if(pos==size-1) {
        // save pemuted results here
        printf("%s\n",arr);
        vector_push_back(result_vector, arr);
        return;
    }
    for (int i=pos; i<size; i++) {
       if(lookup_and_insert(set, arr[i])) continue; // already processed, move on
       //printf("pos: %d i:%d, set:%s arr:%s\n",pos, i, set, arr);
       swap_char(arr, pos, i);
       permute2(arr, pos+1, result_vector); // permute rest of the subarray, assuming prefixes are already permuted
       swap_char(arr, pos,i);   // backtracking, undoing the change we have done earlier
        //printf("backtracking at pos:%d i:%d arr: %s\n",pos,i, arr);
    }
    free(set);
}



