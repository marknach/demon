#include "vector_calc.h"
#include <string.h>

/*
 * Number of time steps to calculate.
 */ 
long number_of_steps;

/*
 * Direction to calculate. If 1, calculate future. Otherwise, calculate past.
 */
int forward;

/*
 * If 1, program behaves as though piping to visualization program.
 * Otherwise, no standard out.
 */ 
int visualsOn;

/*
 * If 1, calcululate time steps indefinitely. Otherwise, calculate number_of_steps
 * time steps.
 */ 
int continuous;

int main(int argc, char *argv[])
{
	/*
	 * If wrong number of arguments is given, print usage and exit.
	 */
	if(argc != 6)
	{
		printf("Usage is: simulation inputfile outputfile direction visualson/visualsoff continuous/steps, where direction is \"forward\" or \"reverse\"\n");
		exit(0);
	}
	
	/**
	 * If forward = 1, the simulation attempts to calculate the future
	 * given initial conditions.
	 * 
	 * If forward = -1, the simulation attempts to calculate the past given
	 * initial conditions.
	 */
    if(strcmp(argv[3],"forward") == 0)
    {
	forward = 1;
    }
    else
    {
        forward = -1;   
    }

	/*
     * If visualsOn is set to 1, then P_x,P_y,r will be output to stdout for each
     * sphere on an interval of 10000 steps. This is intended to be piped to
     * our visualization program.
     */
    if(strcmp(argv[4],"visualson") == 0)
    {
        visualsOn = 1;
    }
    else
    {
        visualsOn = 0;
    }
    
    /*
     * If continuous = 1, then new conditions and timesteps will be computed until
     * the program is manually executed.
     */
    if(strcmp(argv[5],"continuous") == 0)
    {
        continuous = 1;
    }
    
    /*
     * Month being passed as the duration sets a particular number of steps
     * and correspondes to a certain timestep value used for the computation.
     */
    else if(strcmp(argv[5],"month") == 0)
    {
		continuous = 0;
		number_of_steps = 25920000;
    }
    
    /*
     * Otherwise, a number of steps is specified.
     */
    else
    {
        continuous = 0;
		number_of_steps = atoi(argv[5]);
    }

	/*
	 * Initialize starting values from a given input file.
	 */
    initialize_simulation_memory(argv[1], forward);

	/*
	 * If we're driving the simulation, print the number of vectors to prime the
	 * read of the vectors. Then print the initial conditions of each sphere.
	 */ 
    if(visualsOn)
    {
		printf("%d\n",number_of_vectors);	
        for(int i = 0; i < number_of_vectors; i++)
        {
            printf("%lf,%lf,%lf,%lf\n", p[i][0], p[i][1], r[i], m[i]); 
        }
    }
    
    /*
     * Continuously simulate.
     */
	if(continuous)
	{
		long i = 0;
		while(1)
		{
			/*
			 * Calculate next condition of each sphere.
			 */
			calculateNextPositions();

			/*
			 * Print sphere conditions if visuals are to be displayed.
			 */
			if(visualsOn)
			{
				for(int j = 0; j < number_of_vectors; j++)
				{
					if(i % 10000 == 0)
					{
						printf("%lf,%lf,%lf,%lf\n", p[j][0], p[j][1], r[j],m[j]);
					}
				}
			}
			i++;
		}
	}
	
	/*
	 * Finitely many step simulation. Runs for number_of_steps times.
	 */
	else
	{
		for(long i = 0; i < number_of_steps; i++)
		{
			/*
			 * Calculate next condition of each sphere.
			 */
			calculateNextPositions();

			/*
			 * Print sphere conditions if visuals are to be displayed.
			 */
			if(visualsOn)
			{
				for(long j = 0; j < number_of_vectors; j++)
				{
					if(i % 10000 == 0)
					{
						printf("%lf,%lf,%lf\n", p[j][0], p[j][1], r[j]);
					}
				}
			}
		}
		
		
		/*
		 * Outputs final positions to a final before exiting.
		 */ 
		FILE* output_file = fopen(argv[2],"w");
	
		for(int i = 0; i < number_of_vectors; i++)
		{
			 fprintf(output_file,"%-12lf%-12lf%-12lf%-12lf%-12lf\n",p[i][0],p[i][1],v[i][0],v[i][1],r[i]);
		}
		fclose(output_file);
	}
}
