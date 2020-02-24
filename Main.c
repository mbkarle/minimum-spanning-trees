/*----------Import Libraries----------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Heap.h"
#include <stdbool.h>
#include <limits.h>

/*----------Function Headers----------*/
void printMatrix(int numpoints);
double random_num();
double distance_finder(int dim, int i, int j, double coords[][dim]);
void fill_rand(int numpoints);
void free_adj(int numpoints);
double prims(int numpoints); 

Node* vertices;
double** adj_matrix;
Heap H;

/*----------Main----------*/
//command line input: - ./randmst 0 numpoints numtrials dimension
int main(int argc, char* argv[]) {
    srand(time(0) * 100000);
    //seeds the random number generator with current time

    //read inputs
    int numpoints = atoi(argv[2]); 
    printf("%i \n", numpoints);
    int dim = atoi(argv[4]);

    //instantiate n x n adjacency matrix
    adj_matrix = malloc(numpoints * sizeof(double*));
    for(int i = 0; i < numpoints; i++) {
        adj_matrix[i] = malloc(numpoints * sizeof(double));
    }

    //instantiate node array
    vertices = malloc(sizeof(Node) * numpoints);
    for(int i = 0; i < numpoints; i++) {
        vertices[i].idx = i;
        vertices[i].inS = false;
        vertices[i].dist = INT_MAX;
        vertices[i].inH = false;
    }

    
    
    /*----------Case Dim = 0----------*/
    //Fill with random weights in [0, 1]
    if (dim == 0)
    {
        fill_rand(numpoints);
    }

    /*----------Case Dim > 0----------*/
    //Generate random vertex coordinates in R^dim
    else
    {
      double vertex_coords[numpoints][dim];
      for (int i = 0; i < numpoints; i++)
      {
        for (int j = 0; j < dim; j++)
        {
          vertex_coords[i][j] = random_num();
          printf("%lf ", vertex_coords[i][j]);
        }
        printf("\n");
      }
      printf("\n");

      for (int i = 0; i < numpoints; i++)
      {
        for (int j = i + 1; j < numpoints; j++)
        {
            adj_matrix[i][j] = distance_finder(dim, i, j, vertex_coords);
        }
      }
    }

    printMatrix(numpoints);

    /*----------Generate Heap!----------*/ 
    int size = 0;
    H = makeHeap(vertices, numpoints, &size);

    double weight = prims(numpoints);
    printf("Weight: %lf\n", weight);

    /*----------Free Data structures----------*/
    free(H.arr);
    free(vertices);
    free_adj(numpoints); //free adjacency matrix
}

double prims(int numpoints) {
    Node v, w;
    double weight = 0;
    vertices[0].dist = 0; //set source distance to 0
    insert(H, &vertices[0]);

    while(Size(H) != 0) {
        v = *(extractMin(H)); 
        weight += v.dist;
        v.inS = true;
        for(int i = v.idx + 1; i < numpoints; i++) {
            if(!vertices[i].inS && vertices[i].dist > adj_matrix[v.idx][i]) {
                vertices[i].dist = adj_matrix[v.idx][i];
                insert(H, &vertices[i]);
            }
        }
    }
    return weight; //return mst weight
}

double random_num(void) {
    double rand_number = (double)rand() / (double)RAND_MAX;
    return (rand_number);
}

double distance_finder(int dim, int i, int j, double coords[][dim])
{
    double output = 0;
    for (int k = 0; k < dim; k++)
    {
        output = output + pow(coords[i][k]-coords[j][k],2);
    }
    output = sqrt(output);
    return(output);
}

void printMatrix(int numpoints) {
    for (int i = 0; i < numpoints; i++)
    {
      for (int j = 0; j < numpoints; j++)
      {
        printf("%lf ", (adj_matrix[i])[j]);
      }
      printf("\n");
    }
    printf("\n");
}

void fill_rand(int numpoints) {
    for (int i = 0; i < numpoints; i++)
    {
        for (int j = i + 1; j < numpoints; j++)
        {
          adj_matrix[i][j] = random_num();
        }
    }
}

void free_adj(int numpoints) {
    for(int i = 0; i < numpoints; i++) {
        double* currentPtr = adj_matrix[i];
        free(currentPtr);
    }
}
/* Preliminary heap testing
    int num[] = {51, 124, 109, 1, 61, 121, 50, 0, 0, 0, 0};
    int* size = malloc(sizeof(int));
    *size = 7;
    struct Heap heap = makeHeap(num, size);
    int curr = Size(heap);
    for(int i = 0; i < curr; i++) {
        printf("; %i", num[i]);
    }
    printf("\n");
    
    extractMin(heap);
    for(int i = 0; i < Size(heap); i++) {
        printf(", %i", num[i]);
    }
    printf("\n");

    insert(heap, 5);
    for(int i = 0; i < Size(heap); i++) {
        printf(", %i", num[i]);
    }
    printf("\n");

    free(size);
    */
