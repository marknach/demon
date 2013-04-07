#include <math.h>

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

int WallCollide(int **Balls, int size)
{
	int leftwall = 0;
	int rightwall = 8;
	int topwall = 8;
	int bottomwall = 0;

	int i;
	for(i = 0; i < size; i++)
	{
		if(Balls[i][0] <= leftwall || Balls[i][0] >= rightwall)
		{
			return 1;
		}
		else if(Balls[i][1] <= bottomwall || Balls[i][1] >= topwall)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}
