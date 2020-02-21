#include <stdio.h>
#include "Heap.h"

int main(int argc, char* argv[]) {
    int num[] = {51, 124, 109, 1, 61, 121, 50};
    makeHeap(num, 7);
    for(int i = 0; i < 7; i++) {
        printf(", %i", num[i]);
    }
    printf("\n");
}
