#include <stdio.h>
#include <stdlib.h>
int n = 2;

int main()
{
    for(int i = 0; i < n; i++)
    {
	float random = ((float) rand()) / (float) RAND_MAX;
        float px = random * 700;
        random = ((float) rand()) / (float) RAND_MAX;
	float py = random * 700;

	random = ((float) rand()) / (float) RAND_MAX;
	float vx = random * 700;
        random = ((float) rand()) / (float) RAND_MAX;
        float vy = random * 700;

	random = ((float) rand()) / (float) RAND_MAX;
        float ax = random * 700;
        random = ((float) rand()) / (float) RAND_MAX;
        float ay = random * 700;

        printf("%lf	%lf	%lf	%lf	%lf	%lf	20\n",px,py,vx,vy, ax, ay);
    }
}
