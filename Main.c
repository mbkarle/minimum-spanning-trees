#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Heap.h"


//command line input: - ./randmst 0 numpoints numtrials dimension

double random_num();
double distance_finder(int dim, int i, int j, double coords[][dim]);

int main(int argc, char* argv[]) {
    srand(time(0) * 100000);
    //seeds the random number generator with current time

    int numpoints = atoi(argv[2]);
    printf("%i \n", numpoints);
    int dim = atoi(argv[4]);

    double adj_matrix[numpoints][numpoints];

    if (dim == 0)
    {
      for (int i = 0; i < numpoints; i++)
      {
        for (int j = i + 1; j < numpoints; j++)
        {
          adj_matrix[i][j] = random_num();
        }
      }

      for (int i = 0; i < numpoints; i++)
      {
        for (int j = 0; j < i + 1; j++)
        {
          adj_matrix[i][j] = -1;
        }
      }


      for (int i = 0; i < numpoints; i++)
      {
        for (int j = 0; j < numpoints; j++)
        {
          printf("%lf ", adj_matrix[i][j]);
        }
        printf("\n");
      }
      printf("\n");



      /*double vertex_coords[numpoints];
      for (int i = 0; i < numpoints; i++)
      {
          vertex_coords[i] = random_num();
      } */
    }
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

      for (int i = 0; i < numpoints; i++)
      {
        for (int j = 0; j < i + 1; j++)
        {
          adj_matrix[i][j] = -1;
        }
      }

      for (int i = 0; i < numpoints; i++)
      {
        for (int j = 0; j < numpoints; j++)
        {
          printf("%lf ", adj_matrix[i][j]);
        }
        printf("\n");
      }
      printf("\n");


    }




/*    int num[] = {51, 124, 109, 1, 61, 121, 50};
    makeHeap(num, 7);
    for(int i = 0; i < 7; i++) {
        printf(", %i", num[i]);
    }
    printf("\n"); */

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
