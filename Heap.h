#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED
#include <stdlib.h>
#include <stdbool.h>

/*struct Heap {
    int arr[];
    int size;
};*/
void makeHeap(int arr[], int size);
int left(int index);
int right(int index);
int parent(int index);
bool exists(int index, int size);
void swap(int* a, int* b);
void minHeapify(int heap[], int size, int index);

#endif
