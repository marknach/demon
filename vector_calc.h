#ifndef VECT_H
#define VECT_H
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int number_of_vectors;
double **p;
double **v;
double *r;
double *m;

double lower_boundary_x;
double lower_boundary_y;

double upper_boundary_x;
double upper_boundary_y;

double time_step;




void calculateNextPositions();

void initialize_simulation_memory(char *input_filename, int direction);

void detect_wall_collision();

void detect_ball_collision();

void calc_force(int i, int j);

void mdloop();

#endif
