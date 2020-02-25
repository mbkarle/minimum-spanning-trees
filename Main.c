/*----------Import Libraries----------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Heap.h"
#include <stdbool.h>
#include <limits.h>

/*----------Function Headers----------*/
double random_num();
double distance_finder(int dim, int i, int j, Node * vert);
double prims(int numpoints, int dim);
void print_nodes(int numpoints, int dim);

Node* vertices;
double** adj_matrix;
Heap H;

/*----------Main----------*/
//command line input: - ./randmst 0 numpoints numtrials dimension
int main(int argc, char* argv[]) {
    double average;


    srand(time(0) * 100000);
    //seeds the random number generator with current time

    //read inputs
    int numpoints = atoi(argv[2]);
    printf("%i \n", numpoints);
    int dim = atoi(argv[4]);

    //instantiate n x n adjacency matrix
    /*adj_matrix = malloc(numpoints * sizeof(double*));
    for(int i = 0; i < numpoints; i++) {
        adj_matrix[i] = malloc(numpoints * sizeof(double));
    } */

    //instantiate node array
    vertices = malloc(sizeof(Node) * numpoints);
    for(int i = 0; i < numpoints; i++) {
        vertices[i].idx = i;
        vertices[i].inS = false;
        vertices[i].dist = INT_MAX;
        vertices[i].inH = false;
    }

    printf("Vertices Malloced \n");



    /*----------Case Dim = 0----------*/
    //Fill with random weights in [0, 1]
    //if (dim == 0)
    //{
    //  fill_rand(numpoints);
    //}

    /*----------Case Dim > 0----------*/
    //Generate random vertex coordinates in R^dim

        for (int i = 0; i < numpoints; i++)
        {
          for (int j = 0; j < dim; j++)
          {
            vertices[i].coord[j] = random_num();
          }
        }


      /*for (int i = 0; i < numpoints; i++)
      {
        for (int j = i + 1; j < numpoints; j++)
        {
            adj_matrix[i][j] = distance_finder(dim, i, j, vertex_coords);
        }
      }
    }
    printf("Matrix Filled \n"); */

    /*----------Generate Heap!----------*/
    int size = 0;
    H = makeHeap(vertices, numpoints, &size);

    double weight = prims(numpoints, dim);
    printf("Weight: %lf\n", weight);
    print_nodes(numpoints, dim);

    /*----------Free Data structures----------*/
    free(H.arr);
    printf("Freed heap\n");
    free(vertices);
    printf("Freed Vertices\n");

    //free_adj(numpoints); //free adjacency matrix
}

double prims(int numpoints, int dim) {
    Node v, w;
    double weight = 0;
    double distance = 0;
    vertices[0].dist = 0; //set source distance to 0
    insert(H, &vertices[0]);

    while(Size(H) != 0) {
        v = *(extractMin(H));
        weight += v.dist;
        printf("Added edge of weight %lf\n", v.dist);
        v.inS = true;
        for(int i = 0; i < numpoints; i++) {
            if (i != v.idx) {
                distance = distance_finder(dim, v.idx, i, vertices);

                if(!vertices[i].inS && vertices[i].dist > distance) {
                    vertices[i].dist = distance;
                    insert(H, &vertices[i]);
                    isHeap(H);
                }
            }
        }
    }
    return weight; //return mst weight
}

double random_num(void) {
    double rand_number = (double)rand() / (double)RAND_MAX;
    return (rand_number);
}

double distance_finder(int dim, int i, int j, Node * vert)
{
    double output;
    for (int k = 0; k < dim; k++)
    {
        output = output + pow(vert[i].coord[k]-vert[j].coord[k],2);
    }
    output = sqrt(output);
    return(output);
}


void print_nodes(int numpoints, int dim)
{
    for (int i = 0; i < numpoints; i++)
    {
        for (int j = 0; j < dim; j++)
        {
          printf("%lf  ", vertices[i].coord[j]);
        }
        printf("\n");
    }
    printf("\n");
}
