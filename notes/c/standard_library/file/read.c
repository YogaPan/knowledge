#include <stdio.h>
#include <stdlib.h>

#define SIZE 256

void read(FILE *f);

int main(int argc, char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "usage: read filename\n");
		exit(1);
	}

	FILE *fp;
	const char *filename;

	filename = argv[1];
	fp = fopen(filename, "r");
	if (fp)
		read(fp);
	else
		fprintf(stderr, "ERROR\n");
	return 0;
}

void read(FILE *fp)
{
	char buf[SIZE];
	char ch;

	while (fgets(buf, SIZE, fp))
		printf("%s", buf);

	rewind(fp);

	ch = fgetc(fp);
	while (ch != EOF) {
		printf("%c", ch);
		ch = fgetc(fp);
	}
}
