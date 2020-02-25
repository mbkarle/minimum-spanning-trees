/*----------Heap Functions----------*/
#include "Heap.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>


struct Heap;

//move array values into heap order
struct Heap makeHeap(Node* arr, int capacity, int* size) {
    struct Heap h;
    h.arr = malloc(sizeof(Node*) * capacity);
    h.size = size;
    if(*size > 0) {
        for(int i = 0; i < *size; i++) {
            h.arr[i] = &arr[i];
            arr[i].inH = true;
            arr[i].heapIdx = i;
        }
        for(int i = *size/2; i >= 0; i--) {
            minHeapify(h, i);
        }
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
    return (index - 1) / 2;
}

//check index is valid in array
bool exists(int index, int size) {
    return (index < size);
}

//swap nodes at pointers
void swap(Node** a, Node** b) {
    int old_idx = (*a) -> heapIdx; //swap stored indices of heap
    (*(*a)).heapIdx = (*b) -> heapIdx;
    (*(*b)).heapIdx = old_idx;

    Node* temp = *a; //swap what nodes are pointed to at array addresses
    *a = *b;
    *b = temp;
}

bool lessThan(Node* n1, Node* n2) {
    return ((n1 -> dist) < (n2 -> dist));
}

//"fix" heap. Assume children of index are roots of min heaps
void minHeapify(struct Heap heap, int index) {
    Node** arr = heap.arr;
    int size = Size(heap);
    int l = left(index), r = right(index), min;
    min = (exists(l, size) && lessThan(arr[l], arr[index])) ? l : index;
    if(exists(r, size) && lessThan(arr[r], arr[min])) {
        min = r;
    }

    if(min != index) {
        swap(&arr[index], &arr[min]);
        minHeapify(heap, min);
    }
}

//see minimum element without extraction
Node* peek(struct Heap heap) {
    return heap.arr[0];
}

Node* extractMin(struct Heap heap) {
//    isHeap(heap);
    Node* min = heap.arr[0];
    heap.arr[0] = heap.arr[Size(heap) - 1];
    (*(heap.arr[0])).heapIdx = 0;
    *(heap.size) -= 1;
    minHeapify(heap, 0);
    return min;
}

void insert(struct Heap heap, Node* value) { //insert new obj into heap
    Node** arr = heap.arr;
    int i = value -> heapIdx;
    if(!(value -> inH)) {
        i = Size(heap);
        (*(value)).inH = true;
        (*(value)).heapIdx = i;
        arr[i] = value;
        *(heap.size) += 1;
    }
    while(i != 0 && lessThan(arr[i], arr[parent(i)])) {
        swap(&arr[parent(i)], &arr[i]);
        i = parent(i);
    }
}

int Size(struct Heap heap) {
    int curr_size = *(heap.size);
    return curr_size;
}

void printHeap(struct Heap heap) {
    for(int i = 0; i <= floor(log(Size(heap))/log(2)); i++) {
        for(int j = 0; j < pow(2, i); j++) {
            int index = pow(2, i) - 1 + j;
            printf("(N:%i, dist: %lf)     ", heap.arr[index] -> idx, heap.arr[index] -> dist);
        }
        printf("\n");
    }
}

bool isHeap(struct Heap heap) {
    for(int i = 0; i < Size(heap); i++) {
        int l = left(i), r = right(i);
        if((exists(l, Size(heap)) && lessThan(heap.arr[l], heap.arr[i])) || (exists(r, Size(heap)) && lessThan(heap.arr[r], heap.arr[i]))) {
           printf("====================\n");
           printf("ERROR HEAP NOT VALID\n");
           printf("Misplaced index exists at idx = %i\n", i);
           printHeap(heap);
           printf("====================\n");
           return false;
        }
    }
    return true;
}
