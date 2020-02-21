/*----------Heap Functions----------*/
#include "Heap.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#define MAX_SIZE 100000 //change as needed

//struct Heap;

//move array values into heap order
void makeHeap(int arr[], int size) {
    for(int i = size/2; i >= 0; i--) {
        minHeapify(arr, size, i);
    }
}

//return left child index
int left(int index) {
    return index * 2 + 1;
}

//return right child index
int right(int index) {
    return index * 2 + 2;
}

//return parent index
int parent(int index) {
    return index / 2;
}

//check index is valid in array
bool exists(int index, int size) {
    return (index < size);
}

//swap integers at pointers
void swap(int* a, int* b) {
    printf("a: %i\n", *a);
    int temp = *a;
    *a = *b;
    *b = temp;
}

//"fix" heap. Assume children of index are roots of min heaps
void minHeapify(int heap[], int size, int index) {
    int l = left(index), r = right(index), min;
    min = (exists(l, size) && heap[l] < heap[index]) ? l : index;
    if(exists(r, size) && heap[r] < heap[min]) {
        min = r;
    }

    if(min != index) {
        swap(&(heap[index]), &(heap[min]));
        minHeapify(heap, size, min);
    }
}

//see minimum element without extraction
int peek(int heap[]){
    return heap[0];
}

//int extractMin(int heap[])
