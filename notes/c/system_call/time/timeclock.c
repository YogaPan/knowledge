#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define BILLION 1E9

int main(void)
{
	struct timespec start, end;
	float sec;

	clock_gettime(CLOCK_REALTIME, &start);
	sleep(2);
	clock_gettime(CLOCK_REALTIME, &end);

	sec = end.tv_sec - start.tv_sec;
	printf("%f\n", sec);

	clock_gettime(CLOCK_REALTIME, &start);
	clock_gettime(CLOCK_REALTIME, &end);

	sec = (end.tv_nsec - start.tv_nsec)/ BILLION;
	printf("%f\n", sec);

	return 0;
}
