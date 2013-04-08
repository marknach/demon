#include "vector_calc.h"

const int number_of_steps = 50;


int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		printf("Usage is: simulation inputfile outputfile\n");
		exit(0);
	}
	
    initialize_simulation_memory(argv[1], argv[2]);
	
	
	printf("Initial Values:\n");

    printf("%-12s%-12s%-12s%-12s%-12s%-12s\n","P_x","P_y","V_x","V_y","A_x","A_y");
    for(int i = 0; i < number_of_vectors; i++)
    {
        printf("%-12lf%-12lf%-12lf%-12lf%-12lf%-12lf\n", p[i][0], p[i][1], v[i][0], v[i][1], a[i][0], a[i][1]); 
    }
    
    printf("\n");
    
	
	for(int i = 0; i < number_of_steps; i++)
	{
		printf("Calculating New Positions (Step %d)\n", i + 1);
		calculateNextPositions();
		
		printf("%-12s%-12s%-12s%-12s%-12s%-12s\n","P_x","P_y","V_x","V_y","A_x","A_y");
		for(int i = 0; i < number_of_vectors; i++)
		{
			printf("%-12lf%-12lf%-12lf%-12lf%-12lf%-12lf\n", p[i][0], p[i][1], v[i][0], v[i][1], a[i][0], a[i][1]); 
		}
		printf("\n");
	}
	
	close_method();
	
}
