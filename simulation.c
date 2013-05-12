#include "vector_calc.h"
#include <string.h>
int number_of_steps;
int forward;

int visualsOn;
int continuous;

int main(int argc, char *argv[])
{
	if(argc != 6)
	{
		printf("Usage is: simulation inputfile outputfile direction visualson/visualsoff continuous/steps, where direction is \"forward\" or \"reverse\"\n");
		exit(0);
	}
    if(strcmp(argv[3],"continuousforward") == 0)
    {
	forward = 1;
    }
    else
    {
        forward = -1;   
    }

    if(strcmp(argv[4],"visualson") == 0)
    {
        visualsOn = 1;
    }
    else
    {
        visualsOn = 0;
    }
    
    if(strcmp(argv[5],"continuous") == 0)
    {
        continuous = 1;
    }
    else
    {
        continuous = 0;
		number_of_steps = atoi(argv[5]);
    }

    initialize_simulation_memory(argv[1], forward);

    if(visualsOn)
    {
         printf("%d\n",number_of_vectors);	
    }

    if(visualsOn)
    {
        for(int i = 0; i < number_of_vectors; i++)
        {
            printf("%lf,%lf\n", p[i][0], p[i][1]); 
        }
    }
    
    //printf("\n");
    
	if(continuous)
	{
		int i = 0;
		while(1)
		{
			calculateNextPositions();

			if(visualsOn)
			{
				for(int j = 0; j < number_of_vectors; j++)
				{
				if(i % 10000 == 0)
				{
					printf("%lf,%lf\n", p[j][0], p[j][1]);
						}
				}
			}
			i++;
		}
	}
	else
	{
		for(int i = 0; i < number_of_steps; i++)
		{
			calculateNextPositions();

			if(visualsOn)
			{
				for(int j = 0; j < number_of_vectors; j++)
				{
				if(i % 10000 == 0)
				{
					printf("%lf,%lf\n", p[j][0], p[j][1]);
						}
				}
			}
		}
		FILE* output_file = fopen(argv[2],"w");
	
		for(int i = 0; i < number_of_vectors; i++)
		{
			 fprintf(output_file,"%-12lf%-12lf%-12lf%-12lf%-12lf\n",p[i][0],p[i][1],v[i][0],v[i][1],r[i]);
		}
		fclose(output_file);
	}
	
	
	
}
