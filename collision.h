#include <math.h>
#include "vector_calc.h"

int Collision(int **Balls, int size)
{
	//Given the set of Balls in an array
	int i, j;	
	for(i = 0; i < size - 1; i++)
	{
		for(j = i+1; j < size; j++)
		{
			double D = sqrt(((Balls[i][0] - Balls[j][0])^2) + ((Balls[i][1] - Balls[j][1])^2));
			
			if(D < (Balls[i][2] + Balls[j][2]))
			{
				return 1;
			}
		}
	}

	return 0;
}


