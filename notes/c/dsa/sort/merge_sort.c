#include <stdio.h>
#include <stdlib.h>

static void merge(int *array, int *left_array, int left_count,
		int *right_array, int right_count)
{
	int i, j, k;

	i = 0; j = 0; k = 0;

	while (i < left_count && j < right_count) {
		if (left_array[i] < right_array[j])
			array[k++] = left_array[i++];
		else
			array[k++] = right_array[j++];
	}
	while (i < left_count)
		array[k++] = left_array[i++];
	while (j < right_count)
		array[k++] = right_array[j++];
}

void merge_sort(int *array, int size)
{
	int i, mid;
	int *left_array, *right_array;

	if (size < 2)
		return;

	mid = size / 2;

	left_array  = malloc(sizeof(*left_array) * mid);
	right_array = malloc(sizeof(*right_array) * (size - mid));

	for (i = 0; i < mid; i++)
		left_array[i] = array[i];
	for (i = mid; i < size; i++)
		right_array[i-mid] = array[i];

	merge_sort(left_array, mid);
	merge_sort(right_array, size - mid);
	merge(array, left_array, mid, right_array, size - mid);

	free(left_array);
	free(right_array);
}
