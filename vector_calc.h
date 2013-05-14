#ifndef VECT_H
#define VECT_H
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*
 * Number of vectors in current simulation.
 */
int number_of_vectors;

/*
 * Pointer to array of all positions
 */
double **p;
/*
 * Pointer to array of all velocities
 */
double **v;
/*
 * Pointer to array of all radii
 */
double *r;
/*
 * Pointer to array of all masses
 */
double *m;

//least boundary in horizontal direction
double lower_boundary_x;
//least boundary in vertical direction
double lower_boundary_y;

//greatest boundary in horizontal direction
double upper_boundary_x;
//greatest boundary in vertical direction
double upper_boundary_y;

double time_step;



/*
 * Adds one unit of velocity to position, with attention to
 * wall and ball collisions.
 */ 
void calculateNextPositions();

/*
 * Initializes default parameters and memory for positions, velocities, radii, masses. Initializes other parameters from
 * input file.
 */ 
void initialize_simulation_memory(char *input_filename, int direction);

/**
 * Detects if any balls hit a wall and reflect their velocities accordingly.
 */
void detect_wall_collision();

/**
 * Detects if any balls hit another ball and redirect their velocities accordingly.
 */
void detect_ball_collision();

/*
 * Takes in two ints, and calculates the force of ball i on ball j, and modifies their current velocity accordingly.
 */
void calc_force(int i, int j);

/*
 * Loops through all i, j, i != j, calls calc_force, such that all forces for i,j pairs for i !=j is calculated.
 */
void mdloop();

#endif
