#include<stdlib.h>
#include<stdio.h>
#include<time.h>


int main(void)
{
	time_t seed;

	srand((unsigned int)time(&seed));
	for (int x = 0; x <= 20; x++)
	{
		printf("%i\n", rand()%5);
	}
	return 0;
}