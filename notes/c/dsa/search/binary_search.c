#include <stdio.h>

#define ARRAY_SIZE 10

/*
 * Search from array and return index.
 * Return -1 if nothing will be found.
 */
int binary_search(int *array, int size, int key)
{
	int start = 0;
	int end = size;
	int mid;

	while (start <= end) {
		mid = (start + end) / 2;

		if (key == array[mid])
			return mid;
		else if (key < array[mid])
			end = mid - 1;
		else
			start = mid + 1;
	}

	return -1;
}

int main(void)
{
	int ret;
	int array[ARRAY_SIZE] = { 1, 4, 5, 90, 324, 499, 800, 1111, 4213, 9999 };

	ret = binary_search(array, ARRAY_SIZE, 800);
	printf("%d\n", ret);

	return 0;
}
