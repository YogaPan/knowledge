#include <stdio.h>

#define ARRAY_SIZE 10

int main(void)
{
	int i;
	int arr[ARRAY_SIZE] = { 0 };

	for (i = 0; i < ARRAY_SIZE; i++)
		printf("%d\n", arr[i]);

	return 0;
}
