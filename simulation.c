#include "vector_calc.h"

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("Usage is: simulation filename\n");
		exit(0);
	}
    initialize_simulation_memory(argv[1]);
	
	
}
