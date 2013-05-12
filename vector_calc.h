#ifndef VECT_H
#define VECT_H
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int number_of_vectors;
float **p;
float **v;
float *r;
float *m;

float lower_boundary_x;
float lower_boundary_y;

float upper_boundary_x;
float upper_boundary_y;

float time_step;




void calculateNextPositions();

void initialize_simulation_memory(char *input_filename, int direction);

void detect_wall_collision();

void detect_ball_collision();

#endif
