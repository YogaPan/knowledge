#include <stdio.h>

#define swap(x, y) \
({ \
	typeof(x) __tmp = (x); \
	(x) = (y); \
	(y) = __tmp; \
})

static void _quick_sort(int *array, int left, int right)
{
	int i = left;
	int j = right + 1;

	if (left < right) {
		for (;;) {
			while (i + 1 <= right && array[++i] < array[left]);
			while (j - 1 >= left  && array[--j] > array[left]);
			if (i >= j)
				break;
			else
				swap(array[i], array[j]);
		}
		swap(array[left], array[j]);
		_quick_sort(array, left, j - 1);
		_quick_sort(array, j + 1, right);
	}
}

void quick_sort(int *array, int size)
{
	_quick_sort(array, 0, size - 1);
}
