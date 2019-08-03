#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * Generate random number 10 times between 0~99.
 */
int main(void)
{
	int r;
	int i;

	srand(time(NULL));
	for (i = 0; i < 10; i++) {
		r = rand() % 100;
		printf("%d\n", r);
	}

	return 0;
}
