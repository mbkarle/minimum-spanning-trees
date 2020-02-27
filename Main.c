/*----------Import Libraries----------*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include "Heap.h"
#include <stdbool.h>
#include <limits.h>

/*----------Function Headers----------*/
double random_num();
double distance_finder(int dim, int i, int j, Node * vert);
double prims(int numpoints, int dim);
void print_nodes(int numpoints, int dim);
void nextCounter(int numpoints);
struct timeval GetTimeStamp();

Node* vertices;
double** adj_matrix;
Heap H;
int counter;

/*----------Main----------*/
//command line input: - ./randmst 0 numpoints numtrials dimension
int main(int argc, char* argv[]) {
    int numtrials = atoi(argv[3]);
    double total_weight_over_trials = 0;
    int numpoints = atoi(argv[2]);
    int dim = atoi(argv[4]);
    srand(time(0));
    for (int t = 0; t < numtrials; t++)
    {

        double average = 0;
        counter = 0;

        //instantiate node array
        vertices = malloc(sizeof(Node) * numpoints);
        for(int i = 0; i < numpoints; i++) {
            vertices[i].idx = i;
            vertices[i].inS = false;
            vertices[i].dist = INT_MAX;
            vertices[i].inH = false;
        }

        for (int i = 0; i < numpoints; i++)
        {
          for (int j = 0; j < dim; j++)
          {
            vertices[i].coord[j] = random_num();
          }
        }

        /*----------Generate Heap!----------*/
        int size = 0;
        H = makeHeap(vertices, numpoints, &size);

        double weight = prims(numpoints, dim);
        total_weight_over_trials += weight;
        printf("\nWeight: %lf\n", weight);
        //print_nodes(numpoints, dim);

        /*----------Free Data structures----------*/
        free(H.arr);
        free(vertices);
    }
    double average_weight = total_weight_over_trials / (double)numtrials;
    printf("Average weight was %lf over %i trials with n = %i in dimenstion %i", average_weight, numtrials, numpoints, dim);
}

double prims(int numpoints, int dim) {
    Node v, w;
    double weight = 0;
    double distance = 0;
    vertices[0].dist = 0; //set source distance to 0
    insert(H, &vertices[0]);

    while(Size(H) != 0) {
        v = *(extractMin(H));
        weight += (dim != 0) ? sqrt(v.dist) : v.dist; //dist values are actually edge weights squared!
        nextCounter(numpoints);
        //printf("Added edge of weight %lf\n", v.dist);
        v.inS = true;
        for(int i = 0; i < numpoints; i++) {
            if (i != v.idx) {
                if (dim != 0) {
                    distance = distance_finder(dim, v.idx, i, vertices);
                }
                else {
                    distance = random_num();
                }

                if(!vertices[i].inS && vertices[i].dist > distance) {
                    vertices[i].dist = distance;
                    insert(H, &vertices[i]);
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
    double output = 0;
    for (int k = 0; k < dim; k++)
    {
        output = output + (vert[i].coord[k]-vert[j].coord[k])*(vert[i].coord[k]-vert[j].coord[k]);
    }
    //output = sqrt(output); Don't in fact square root values until accurate value is truly needed
    //printf("edges %i to %i have weight: %lf\n", i, j, output);
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

void nextCounter(int numpoints) {
    counter++;
    if(counter % 1000 == 0) {
        printf("\rNodes in tree: %i / %i", counter, numpoints);
        fflush(stdout);
    }
}

struct timeval GetTimeStamp() {
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv;
}
