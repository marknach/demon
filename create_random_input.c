#include <stdio.h>
#include <stdlib.h>
int n = 27;

int main()
{
    for(int i = 0; i < n; i++)
    {
	float random = ((float) rand()) / (float) RAND_MAX;
        float px = random * 4;
        random = ((float) rand()) / (float) RAND_MAX;
	float py = random * 3;

	random = ((float) rand()) / (float) RAND_MAX;
	float vx = random * 4;
        random = ((float) rand()) / (float) RAND_MAX;
        float vy = random * 3;


        printf("%lf	%lf	%lf	%lf	1\n",px,py,vx,vy);
    }
}
