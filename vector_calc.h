#ifndef VECT_H
#define VECT_H
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int number_of_vectors;
float **p;
float **v;
float **a;
float *r;

float lower_boundary_x;
float lower_boundary_y;

float upper_boundary_x;
float upper_boundary_y;

float time_step;

FILE* input_file;
FILE* output_file;


void calculateNextPositions();

void initialize_simulation_memory(char *input_filename, char *output_filename);

void detect_wall_collision();

void detect_ball_collision();

void close_method();

#endif
