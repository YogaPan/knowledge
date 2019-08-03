#include <stdio.h>

#define FALSE 0
#define TRUE 1

#define swap(x, y) \
({ \
	typeof(x) __tmp = (x); \
	(x) = (y); \
	(y) = __tmp; \
})

void bubble_sort(int *array, int size)
{
	int i, j;
	int flags = TRUE;

	for (i = 0; i < size - 1 && flags; i++) {
		for (j = 0; j < size - i - 1; j++) {
			flags = FALSE;
			if (array[j] > array[j+1]) {
				swap(array[j], array[j+1]);
				flags = TRUE;
			}
		}
	}
}
