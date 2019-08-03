#include <stdio.h>
#include <time.h>

void waste_time(void);

int main(void)
{
	clock_t start;
	clock_t spend;

	start = clock();
	waste_time();
	spend = (clock() - start) / CLOCKS_PER_SEC;

	printf("Spend %ld seconds.\n", spend);

	return 0;
}

void waste_time(void)
{
	int i;

	for (i = 0; i < 1000000000; i++);
}
