#include "vector_calc.h"
#define DEBUG

#ifdef DEBUG
#include <stdio.h>
#endif


//Adding one unit of time velocity to position.
void calculateNextPositions()
{
	for(int i = 0; i < number_of_vectors - 1; i++)
	{
		fprintf(output_file,"%lf,%lf,",p[i][0],p[i][1]);
		p[i][0] += time_step * v[i][0];
		p[i][1] += time_step * v[i][1];
		
	}
	
	int i = number_of_vectors - 1;
	fprintf(output_file,"%lf,%lf",p[i][0],p[i][1]);
	p[i][0] += time_step * v[i][0];
	p[i][1] += time_step * v[i][1];
	
	fprintf(output_file,"\n");
	
	
	detect_wall_collision();
}

void initialize_simulation_memory(char *input_filename, char *output_filename)
{
    upper_boundary_x = 4;
	upper_boundary_y = 8;

	
	time_step = 0.1;
	
	
	input_file = fopen(input_filename, "r");
	output_file = fopen(output_filename, "w");
	if(input_file == 0)
	{
		printf("input_file file %s not found.\n",input_filename);
		exit(1); 
	}
	
	char line[256];
	number_of_vectors = 0;
	
	while (fgets(line, 256, input_file))
		number_of_vectors++;
	
	
	printf("\n");
	printf("Reading %d from %s.\n\n",number_of_vectors,input_filename);
	p = (float **)malloc(number_of_vectors * sizeof(float *));
    v = (float **)malloc(number_of_vectors * sizeof(float *));
    a = (float **)malloc(number_of_vectors * sizeof(float *));
	
	fclose(input_file);
	
	
    for(int i = 0; i < number_of_vectors; i++)
    {
		p[i] = (float *)malloc(2 * sizeof(float ));
		v[i] = (float *)malloc(2 * sizeof(float ));
		a[i] = (float *)malloc(2 * sizeof(float ));
    }
	
	input_file = fopen(input_filename, "r");
    for(int i = 0; i < number_of_vectors; i++)
    {
		fscanf(input_file,"%f",&p[i][0]);
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
		
		fscanf(input_file,"%f",&p[i][1]);
		if(p[i][1] >= upper_boundary_y)
		{
			fprintf(stderr,"P_%d_x, value %lf exceeds boundary %lf\n",2, p[i][1], upper_boundary_y);
			fprintf(stderr,("Program will now exit.\n"));
			exit(1);
		}
		else if(p[i][1] <= lower_boundary_y)
		{
			fprintf(stderr,"P_%d_x, value %lf exceeds boundary %lf\n",2, p[i][1], lower_boundary_y);
			fprintf(stderr,("Program will now exit.\n"))	;
			exit(1);
		}
		
		
		fscanf(input_file,"%f",&v[i][0]);
		fscanf(input_file,"%f",&v[i][1]);
		
		fscanf(input_file,"%f",&a[i][0]);
		fscanf(input_file,"%f",&a[i][1]);
    }
	fclose(input_file);
}



void detect_wall_collision()
{
	for(int i = 0; i < number_of_vectors; i++)
	{
		//hits vertical wall
		//reverse
		if(p[i][0] <= lower_boundary_x)
		{
			v[i][0] = -1 * v[i][1];
			p[i][0] = lower_boundary_x + 0.00001f; //hacky way of making sure the balls don't leave the boundaries
		}
		else if(p[i][0] >= upper_boundary_x)
		{
			v[i][0] = -1 * v[i][1];
			p[i][0] = upper_boundary_x - 0.00001f; //hacky way of making sure the balls don't leave the boundaries
		}
		//hits horizontal wall
		if(p[i][1] <= lower_boundary_y)
		{
			v[i][1] = -1 * v[i][1];
			p[i][1] = lower_boundary_y + 0.00001f; //hacky way of making sure the balls don't leave the boundaries
		}
		else if(p[i][1] >= upper_boundary_y)
		{
			v[i][1] = -1 * v[i][1];
			p[i][1] = upper_boundary_y - 0.00001f; //hacky way of making sure the balls don't leave the boundaries
		}
	}
}


//This needs to be called to clean things up.
void close_method()
{
	fclose(output_file);
}
