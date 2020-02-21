#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED
#include <stdlib.h>
#include <stdbool.h>
#define MAX_SIZE 100000 //change as needed

struct Heap {
    int *arr;
    int *size;
};
struct Heap makeHeap(int* arr, int* size);
int left(int index);
int right(int index);
int parent(int index);
bool exists(int index, int size);
void swap(int* a, int* b);
void minHeapify(struct Heap heap, int index);
int peek(struct Heap heap);
int extractMin(struct Heap heap);
void insert(struct Heap heap, int value);
int Size(struct Heap heap);

#endif
