#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED
#include <stdlib.h>
#include <stdbool.h>
#define MAX_SIZE 100000 //change as needed

/*----------Struct Definition----------*/
typedef struct Node {
    int idx; //id in adj_matrix to access and handle nodes
    int heapIdx; //index in heap
    bool inH; //is it in the heap?
    bool inS; //is it in S? initialize to false and change when added to MST
    double dist; //current known distance from S to node
    double coord[4];

} Node;

typedef struct Heap {
    Node** arr; //array of pointers to nodes
    int* size; //pointer to size variable
} Heap;

/*----------Function Headers----------*/
struct Heap makeHeap(Node* arr, int capacity, int* size);
int left(int index);
int right(int index);
int parent(int index);
bool exists(int index, int size);
void swap(Node** a, Node** b);
bool lessThan(Node* n1, Node* n2);
void minHeapify(struct Heap heap, int index);
Node* peek(struct Heap heap);
Node* extractMin(struct Heap heap);
void insert(struct Heap heap, Node* value);
int Size(struct Heap heap);
void printHeap(struct Heap heap);
bool isHeap(struct Heap heap);

#endif
