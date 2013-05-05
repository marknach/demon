#include "vector_calc.h"
#include <string.h>
const int number_of_steps = 500000;
int forward;

int main(int argc, char *argv[])
{
	if(argc != 4)
	{
		printf("Usage is: simulation inputfile outputfile direction, where direction is \"forward\" or \"reverse\"\n");
		exit(0);
	}
    if(strcmp(argv[3],"forward"))
    {
	forward = 1;
    }
    else
    {
        forward = -1;   
    }

    initialize_simulation_memory(argv[1], forward);
    printf("%d\n",number_of_vectors);	
    

    for(int i = 0; i < number_of_vectors; i++)
    {
        printf("%lf,%lf\n", p[i][0], p[i][1]); 
    }
    
    //printf("\n");
    
	
    for(int i = 0; i < number_of_steps; i++)
	{
		calculateNextPositions();
		for(int i = 0; i < number_of_vectors; i++)
		{
			 printf("%lf,%lf\n", p[i][0], p[i][1]);
		}
	}
	
	FILE* output_file = fopen(argv[2],"w");
	
	for(int i = 0; i < number_of_vectors; i++)
	{
		 fprintf(output_file,"%-12lf%-12lf%-12lf%-12lf%-12lf\n",p[i][0],p[i][1],v[i][0],v[i][1],r[i]);
	}
	fclose(output_file);
	
}
