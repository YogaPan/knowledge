#include <stdio.h>
#include <stdlib.h>

static int array[] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };

void print_array(int *array, int size)
{
	int i;

	for (i = 0; i < size; i++)
		printf("%d ", array[i]);
}

int cmp(const void *xp, const void *yp)
{
	int x = *(int *)xp;
	int y = *(int *)yp;

	return x > y ? 1 : -1;
}

int main(void)
{
	qsort(array, 3, sizeof(array[0]), cmp);
	print_array(array, 8);

	return 0;
}
