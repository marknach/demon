#include "vector_calc.h"
#define DEBUG

#ifdef DEBUG
#include <stdio.h>
#endif



// 
void calculateNextPositions()
{
	printf("Calculating New Positions:\n");
	for(int i = 0; i < number_of_vectors; i++)
	{
		p[i][0] += v[i][0];
		p[i][1] += v[i][1];
		p[i][2] += v[i][2];
	}
}


// char *file_name : input file with initialization vectors
void initialize_simulation_memory(char *file_name)
{
	// maybe global?
    boundary_x = 4;
	boundary_y = 8;
	
	
	FILE* input = fopen(file_name, "r");
	if(input == 0)
	{
		printf("Input file %s not found.\n",file_name);
		exit(1); 
	}
	
	
	char line[256];
	number_of_vectors = 0;
	
	while (fgets(line, 256, input))
		number_of_vectors++;
	
	printf("\n");
	printf("Reading %d from %s.\n\n",number_of_vectors,file_name);
	p = (float **)malloc(number_of_vectors * sizeof(float *));
    v = (float **)malloc(number_of_vectors * sizeof(float *));
    a = (float **)malloc(number_of_vectors * sizeof(float *));
	
	fclose(input);
	input = fopen(file_name, "r");
	
    for(int i = 0; i < number_of_vectors; i++)
    {
		p[i] = (float *)malloc(3 * sizeof(float ));
		v[i] = (float *)malloc(3 * sizeof(float ));
		/*a[i] = (float *)malloc(3 * sizeof(float ));*/
    }
	
	
    for(int i = 0; i < number_of_vectors; i++)
    {
		fscanf(input,"%f",&p[i][0]);
		if(p[i][0] >= boundary_x)
		{
			fprintf(stderr,"P_%d_x, value %lf exceeds boundary %lf\n",1, p[i][0], boundary_x);
			fprintf(stderr,"Replacing %lf with %lf\n", p[i][0], fmod(p[i][0], boundary_x));
			p[i][0] = fmod(p[i][0], boundary_x);
			printf("\n");
		}
		fscanf(input,"%f",&p[i][1]);
		
		if(p[i][1] >= boundary_x)
		{
			fprintf(stderr,"P_%d_x, value %lf exceeds boundary %lf\n",2, p[i][1], boundary_x);
			fprintf(stderr,"Replacing %lf with %lf\n", p[i][0], fmod(p[i][1], boundary_x));
			p[i][1] = fmod(p[i][1], boundary_x);
			printf("\n");
		}
		
		
		fscanf(input,"%f",&p[i][2]);
		
		if(p[i][2] >= boundary_x)
		{
			fprintf(stderr,"P_%d_x, value %lf exceeds boundary %lf\n",3, p[i][2], boundary_x);
			fprintf(stderr,"Replacing %lf with %lf\n", p[i][2], fmod(p[i][2], boundary_x));
			p[i][2] = fmod(p[i][2], boundary_x);
			printf("\n");
		}
		
		fscanf(input,"%f",&v[i][0]);
		fscanf(input,"%f",&v[i][1]);
		fscanf(input,"%f",&v[i][2]);
    }
    
    
    printf("Initial Values:\n");

    #ifdef DEBUG
    printf("%-12s%-12s%-12s%-12s%-12s%-12s\n","P_x","P_y","P_z","V_x","V_y","V_z");
    for(int i = 0; i < number_of_vectors; i++)
    {
        printf("%-12lf%-12lf%-12lf%-12lf%-12lf%-12lf\n", p[i][0], p[i][1], p[i][2], v[i][0], v[i][1], v[i][2]); 
    }
    
    printf("\n");
    
    calculateNextPositions();
    
    printf("%-12s%-12s%-12s%-12s%-12s%-12s\n","P_x","P_y","P_z","V_x","V_y","V_z");
    for(int i = 0; i < number_of_vectors; i++)
    {
        printf("%-12lf%-12lf%-12lf%-12lf%-12lf%-12lf\n", p[i][0], p[i][1], p[i][2], v[i][0], v[i][1], v[i][2]); 
    }
    #endif

	fclose(input);
}
