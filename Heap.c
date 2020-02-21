/*----------Heap Functions----------*/
#include "Heap.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>


struct Heap;

//move array values into heap order
struct Heap makeHeap(int* arr, int* size) {
    struct Heap h;
    h.arr = arr;
    h.size = size;
    for(int i = *size/2; i >= 0; i--) {
        minHeapify(h, i);
    }
    return h;
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
    int temp = *a;
    *a = *b;
    *b = temp;
}

//"fix" heap. Assume children of index are roots of min heaps
void minHeapify(struct Heap heap, int index) {
    int* arr = heap.arr;
    int size = Size(heap);
    int l = left(index), r = right(index), min;
    min = (exists(l, size) && arr[l] < arr[index]) ? l : index;
    if(exists(r, size) && arr[r] < arr[min]) {
        min = r;
    }

    if(min != index) {
        swap(&(arr[index]), &(arr[min]));
        minHeapify(heap, min);
    }
}

//see minimum element without extraction
int peek(struct Heap heap) {
    return heap.arr[0];
}

int extractMin(struct Heap heap) {
    int min = heap.arr[0];
    heap.arr[0] = heap.arr[Size(heap) - 1];
    *(heap.size) -= 1;
    minHeapify(heap, 0);
    return min;
}

void insert(struct Heap heap, int value) { //insert new obj into heap
    int* arr = heap.arr;
    int i = Size(heap);
    arr[i] = value;
    *(heap.size) += 1;
    while(i != 0 && arr[parent(i)] > arr[i]) {
        swap(&arr[parent(i)], &arr[i]);
        i = parent(i);
    }
}

int Size(struct Heap heap) {
    int curr_size = *(heap.size);
    return curr_size;
}
