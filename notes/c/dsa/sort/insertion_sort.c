#include <stdio.h>

void insertion_sort(int *array, int size)
{
	int tmp;
	int i, j;

	for (i = 1; i < size; i++) {
		tmp = array[i];

		for (j = i; j > 0 && tmp < array[j-1]; j--)
			array[j] = array[j-1];

		array[j] = tmp;
	}
}
