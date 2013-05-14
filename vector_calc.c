#include "vector_calc.h"


/*
 * Adds one unit of velocity to position, with attention to
 * wall and ball collisions.
 */ 
void calculateNextPositions()
{
	for(int i = 0; i < number_of_vectors; i++)
	{
		mdloop();
		p[i][0] += time_step * v[i][0];
		p[i][1] += time_step * v[i][1];
	}
	
	detect_ball_collision();
	detect_wall_collision();
}

/*
 * Initializes default parameters and memory for positions, velocities, radii, masses. Initializes other parameters from
 * input file.
 */ 
void initialize_simulation_memory(char *input_filename,  int direction)
{
    upper_boundary_x = 4;
	upper_boundary_y = 3;

	
	time_step = 0.0000001;
	
	
	FILE* input_file = fopen(input_filename, "r");
	if(input_file == 0)
	{
		printf("input_file file %s not found.\n",input_filename);
		exit(1); 
	}
	
	char line[256];
	number_of_vectors = 0;
	
	while (fgets(line, 256, input_file))
		number_of_vectors++;
	
	
	//printf("\n");
	//printf("Reading %d from %s.\n\n",number_of_vectors,input_filename);
        p = (double **)malloc(number_of_vectors * sizeof(double *));
        v = (double **)malloc(number_of_vectors * sizeof(double *));
        r = (double *)malloc(number_of_vectors * sizeof(double *));
        m = (double *)malloc(number_of_vectors * sizeof(double *));
	
	fclose(input_file);
	
	
    for(int i = 0; i < number_of_vectors; i++)
    {
		p[i] = (double *)malloc(2 * sizeof(double ));
		v[i] = (double *)malloc(2 * sizeof(double ));
    }
	
	input_file = fopen(input_filename, "r");
    for(int i = 0; i < number_of_vectors; i++)
    {
		fscanf(input_file,"%lf",&p[i][0]);
		if(p[i][0] >= upper_boundary_x)
		{
			fprintf(stderr,"P_%d_x, value %lf exceeds boundary %lf\n",1, p[i][0], upper_boundary_x);
			fprintf(stderr,("Program will now exit.\n"));
			exit(1);
		}
		else if(p[i][0] <= lower_boundary_x)
		{
			fprintf(stderr,"P_%d_x, value %lf exceeds boundary %lf\n",1, p[i][0], lower_boundary_x);
			fprintf(stderr,("Program will now exit.\n"));
			exit(1);
		}
		
		fscanf(input_file,"%lf",&p[i][1]);
		if(p[i][1] >= upper_boundary_y)
		{
			fprintf(stderr,"P_%d_y, value %lf exceeds boundary %lf\n",2, p[i][1], upper_boundary_y);
			fprintf(stderr,("Program will now exit.\n"));
			exit(1);
		}
		else if(p[i][1] <= lower_boundary_y)
		{
			fprintf(stderr,"P_%d_y, value %lf exceeds boundary %lf\n",2, p[i][1], lower_boundary_y);
			fprintf(stderr,("Program will now exit.\n"))	;
			exit(1);
		}
		
		
		fscanf(input_file,"%lf",&v[i][0]);
		v[i][0] *= direction;
		fscanf(input_file,"%lf",&v[i][1]);
		v[i][1] *= direction;
		
		fscanf(input_file,"%lf",&r[i]);
		
		fscanf(input_file,"%lf",&m[i]);
    }
	fclose(input_file);
}


/**
 * Detects if any balls hit a wall and reflect their velocities accordingly.
 */
void detect_wall_collision()
{
	for(int i = 0; i < number_of_vectors; i++)
	{
		//hits vertical wall
		//reverse
		if(p[i][0] - r[i] < lower_boundary_x)
		{	
			v[i][0] = -1 * v[i][0];
			p[i][0] = lower_boundary_x + r[i]; //hacky way of making sure the balls don't leave the boundaries
		}
		else if(p[i][0] + r[i] > upper_boundary_x)
		{
			v[i][0] = -1 * v[i][0];
			p[i][0] = upper_boundary_x - r[i]; //hacky way of making sure the balls don't leave the boundaries
		}
		//hits horizontal wall
		if(p[i][1] - r[i] < lower_boundary_y)
		{
			v[i][1] = -1 * v[i][1];
			p[i][1] = lower_boundary_y + r[i]; //hacky way of making sure the balls don't leave the boundaries
		}
		else if(p[i][1] + r[i] > upper_boundary_y)
		{
			v[i][1] = -1 * v[i][1];
			p[i][1] = upper_boundary_y - r[i]; //hacky way of making sure the balls don't leave the boundaries
		}
	}
}

/**
 * Detects if any balls hit another ball and redirect their velocities accordingly.
 */
void detect_ball_collision()
{
	//Given the set of Balls in an array
	int i, j;	
	for(i = 0; i < number_of_vectors - 1; i++)
	{
		for(j = i+1; j < number_of_vectors; j++)
		{
			double collision[2];
			collision[0] = p[i][0] - p[j][0];
			collision[1] = p[i][1] - p[j][1];
			double D = sqrt(((p[i][0] - p[j][0]) * (p[i][0] - p[j][0])) + ((p[i][1] - p[j][1]) * (p[i][1] - p[j][1])));
			
			if(D == 0.0f)
			{
				collision[0] = 1;
				collision[1] = 0;
				D = 1.0f;
			}
			//printf("D = %lf\n", D);
			if(D < r[i] + r[j])
			{/**
 * Detects if any balls hit another ball and redirect their velocities accordingly.
 */
				collision[0] /= D;
				collision[1] /= D;
				double aci = v[i][0] * collision[0] + v[i][1] * collision[1]; 
				double bci = v[j][0] * collision[0] + v[j][1] * collision[1];

				double acf = bci;
				double bcf = aci;

				v[i][0] += (acf - aci) * collision[0];
				v[i][1] += (acf - aci) * collision[1];
				v[j][0] += (bcf - bci) * collision[0];
				v[j][1] += (bcf - bci) * collision[1];
			}
		}
	}
}

/*
 * Takes in two ints, and calculates the force of ball i on ball j, and modifies their current velocity accordingly.
 */
void calc_force(int i, int j)
{
	double fx = 12*( (1/(abs(r[i]-r[j])^14))-(1/(abs(r[i]-r[j])^8)))*(p[i][1]-p[j][1]);
	double fy = 12*( (1/(abs(r[i]-r[j])^14))-(1/(abs(r[i]-r[j])^8)))*(p[i][2]-p[j][2]);
	
	//Calculates acceleration from f=ma
	double ax1 = fx / m[i];
	double ay1 = fy / m[i];
	double ax2 = fx / m[j];
	double ay2 = fy / m[j];
	
	//Uses acceleration to modify velocity in this step
	v[i][1] += time_step * ax1;
	v[i][2] += time_step * ay1;
	v[j][1] += time_step * ax2;
	v[j][2] += time_step * ay2;
}

/*
 * Loops through all i, j, i != j, calls calc_force, such that all forces for i,j pairs for i !=j is calculated.
 */
void mdloop()
{
	int i, j;	
	for(i = 0; i < number_of_vectors - 1; i++)
	{
		for(j = i+1; j < number_of_vectors; j++)
		{
			calc_force(i,j);
		}
	}
}
