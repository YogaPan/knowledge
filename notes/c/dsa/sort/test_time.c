#include <stdio.h>
#include <time.h>

void insertion_sort(int *array, int size);
void selection_sort(int *array, int size);
void bubble_sort(int *array, int size);
void heap_sort(int *array, int size);
void merge_sort(int *array, int size);
void quick_sort(int *array, int size);
void radix_sort(int *array, int size);

double diff_in_second(struct timespec start, struct timespec end)
{
	struct timespec diff;

	if (end.tv_nsec - start.tv_nsec < 0) {
		diff.tv_sec  = end.tv_sec - start.tv_sec - 1;
		diff.tv_nsec = end.tv_nsec - start.tv_nsec + 1000000000;
	} else {
		diff.tv_sec  = end.tv_sec - start.tv_sec;
		diff.tv_nsec = end.tv_nsec - start.tv_nsec;
	}
	return (diff.tv_sec + diff.tv_nsec / 1000000000.0);
}

void print_array(int *array)
{
	int i;

	for (i = 0; i < ARRAY_SIZE; i++)
		printf("%d ", array[i]);
	printf("\n");
}

int main(void)
{
	struct timespec start, end;
	FILE *read_fp, *write_fp;
	int array[ARRAY_SIZE];
	int i, j;
	double diff;

	read_fp = fopen(RANDOM_FILE, "r");

	/* insertion sort */
	printf("insertion sort\n");
	write_fp = fopen("./insertion_sort.txt", "w");
	for (i = 0; i <= ARRAY_SIZE; i += 250) {
		for (j = 0; j < i; j++)
			fscanf(read_fp, "%d", &array[j]);
		clock_gettime(CLOCK_REALTIME, &start);
		insertion_sort(array, i);
		clock_gettime(CLOCK_REALTIME, &end);
		diff = diff_in_second(start, end);
		fprintf(write_fp, "%5d data: %f seconds\n", i, diff);
		rewind(read_fp);
	}
	/* print_array(array, ARRAY_SIZE); */

	/* selection sort */
	printf("selection sort\n");
	write_fp = fopen("./selection_sort.txt", "w");
	for (i = 0; i <= ARRAY_SIZE; i += 250) {
		for (j = 0; j < i; j++)
			fscanf(read_fp, "%d", &array[j]);
		clock_gettime(CLOCK_REALTIME, &start);
		selection_sort(array, i);
		clock_gettime(CLOCK_REALTIME, &end);
		diff = diff_in_second(start, end);
		fprintf(write_fp, "%5d data: %f seconds\n", i, diff);
		rewind(read_fp);
	}
	/* print_array(array, ARRAY_SIZE); */

	/* bubble sort */
	printf("bubble sort\n");
	write_fp = fopen("./bubble_sort.txt", "w");
	for (i = 0; i <= ARRAY_SIZE; i += 250) {
		for (j = 0; j < i; j++)
			fscanf(read_fp, "%d", &array[j]);
		clock_gettime(CLOCK_REALTIME, &start);
		bubble_sort(array, i);
		clock_gettime(CLOCK_REALTIME, &end);
		diff = diff_in_second(start, end);
		fprintf(write_fp, "%5d data: %f seconds\n", i, diff);
		rewind(read_fp);
	}
	/* print_array(array, ARRAY_SIZE); */

	/* heap sort */
	printf("heap sort\n");
	write_fp = fopen("./heap_sort.txt", "w");
	for (i = 0; i <= ARRAY_SIZE; i += 250) {
		for (j = 0; j < i; j++)
			fscanf(read_fp, "%d", &array[j]);
		clock_gettime(CLOCK_REALTIME, &start);
		heap_sort(array, i);
		clock_gettime(CLOCK_REALTIME, &end);
		diff = diff_in_second(start, end);
		fprintf(write_fp, "%5d data: %f seconds\n", i, diff);
		rewind(read_fp);
	}
	/* print_array(array, ARRAY_SIZE); */

	/* merge sort */
	printf("merge sort\n");
	write_fp = fopen("./merge_sort.txt", "w");
	for (i = 0; i <= ARRAY_SIZE; i += 250) {
		for (j = 0; j < i; j++)
			fscanf(read_fp, "%d", &array[j]);
		clock_gettime(CLOCK_REALTIME, &start);
		merge_sort(array, i);
		clock_gettime(CLOCK_REALTIME, &end);
		diff = diff_in_second(start, end);
		fprintf(write_fp, "%5d data: %f seconds\n", i, diff);
		rewind(read_fp);
	}
	/* print_array(array, ARRAY_SIZE); */

	/* quick sort */
	printf("quick sort\n");
	write_fp = fopen("./quick_sort.txt", "w");
	for (i = 0; i <= ARRAY_SIZE; i += 250) {
		for (j = 0; j < i; j++)
			fscanf(read_fp, "%d", &array[j]);
		clock_gettime(CLOCK_REALTIME, &start);
		quick_sort(array, i);
		clock_gettime(CLOCK_REALTIME, &end);
		diff = diff_in_second(start, end);
		fprintf(write_fp, "%5d data: %f seconds\n", i, diff);
		rewind(read_fp);
	}
	/* print_array(array, ARRAY_SIZE); */

	/* radix sort */
	printf("radix sort\n");
	write_fp = fopen("./radix_sort.txt", "w");
	for (i = 0; i <= ARRAY_SIZE; i += 250) {
		for (j = 0; j < i; j++)
			fscanf(read_fp, "%d", &array[j]);
		clock_gettime(CLOCK_REALTIME, &start);
		quick_sort(array, i);
		clock_gettime(CLOCK_REALTIME, &end);
		diff = diff_in_second(start, end);
		fprintf(write_fp, "%5d data: %f seconds\n", i, diff);
		rewind(read_fp);
	}
	/* print_array(array, ARRAY_SIZE); */

	fclose(read_fp);

	return 0;
}
