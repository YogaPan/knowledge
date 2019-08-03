#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int find_largest(int *array, int size)
{
	int i;
	int largest = -1;

	for (i = 0; i < size; i++) {
		if (array[i] > largest)
			largest = array[i];
	}

	return largest;
}

void radix_sort(int *array, int size)
{
	int i;
	int *semi_sorted;
	int largest;
	int digit = 1;

	semi_sorted = malloc(sizeof(*semi_sorted) * size);

	largest = find_largest(array, size);

	while (largest / digit > 0) {
		int bucket[10] = { 0 };

		for (i = 0; i < size; i++)
			bucket[(array[i] / digit) % 10]++;

		for (i = 1; i < 10; i++)
			bucket[i] += bucket[i - 1];

		for (i = size - 1 ; i >= 0; i--)
			semi_sorted[--bucket[(array[i] / digit) % 10]] = array[i];

		for (i = 0; i < size; i++)
			array[i] = semi_sorted[i];

		digit *= 10;
	}

	free(semi_sorted);
}
