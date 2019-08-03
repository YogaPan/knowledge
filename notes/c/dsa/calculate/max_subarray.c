#include <stdio.h>

#define ARRAY_SIZE 10

static inline int max(int x, int y)
{
	return x > y ? x : y;
}

/* Kadane's algorithm */
int max_subarray(int *array, int size)
{
	int i;
	int ans = 0;
	int sum = 0;

	for (i = 0; i < size; i++) {
		if (sum + array[i] > 0)
			sum += array[i];
		else
			sum = 0;

		ans = max(ans, sum);
	}

	return ans;
}

int main(void)
{
	int i;
	int ret;
	int array[ARRAY_SIZE] = { 0, -4, 9, -8, 2, -5, -6, -8, 10, -1 };

	ret = max_subarray(array, 10);
	for (i = 0; i < ARRAY_SIZE; i++)
		printf("%d ", array[i]);
	printf("\nmax sum is: %d\n", ret);

	return 0;
}
