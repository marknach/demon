#ifndef VECT_H
#define VECT_H
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int number_of_vectors;
float **p;
float **v;
float **a;

float boundary_x;
float boundary_y;

void calculateNextPositions();

void initialize_simulation_memory(char *file_name);


#endif
