#include <stdio.h>
#include <time.h>
#include "hash.h"

#define DICT_FILE "./dictionary/words.txt"
#define BUFFER_SIZE 64

static char buffer[BUFFER_SIZE];

static double diff_in_second(struct timespec t1, struct timespec t2)
{
	struct timespec diff;

	if (t2.tv_nsec-t1.tv_nsec < 0) {
		diff.tv_sec  = t2.tv_sec - t1.tv_sec - 1;
		diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
	} else {
		diff.tv_sec  = t2.tv_sec - t1.tv_sec;
		diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
	}
	return (diff.tv_sec + diff.tv_nsec / 1000000000.0);
}

int main(void)
{
	int i;
	double diff;
	FILE *fp;
	struct dict *dict;
	struct timespec start, end;

	fp = fopen(DICT_FILE, "r");

	for (i = 1; i <= 32768; i *= 2) {
		dict = dict_init(i);

		while (fscanf(fp, "%s", buffer) != EOF)
			dict_add(dict, buffer, NULL);

		clock_gettime(CLOCK_REALTIME, &start);

		/*
		if (dict_search(dict, "yoga"))
			printf("yoga found\n");
		else
			printf("yoga not found\n");
		if (dict_search(dict, "james"))
			printf("james found\n");
		else
			printf("james not found\n");
		if (dict_search(dict, "curry"))
			printf("curry found\n");
		else
			printf("curry not found\n");
		*/
		dict_search(dict, "curry");
		dict_search(dict, "yoga");
		dict_search(dict, "james");

		clock_gettime(CLOCK_REALTIME, &end);

		dict_destroy(dict);

		diff = diff_in_second(start, end);
		printf("%d bucket size: %f seconds\n", i,  diff);

		rewind(fp);
	}

	fclose(fp);

	return 0;
}
