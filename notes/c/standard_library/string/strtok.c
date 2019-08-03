#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(void)
{
	const char *s = "Speech is si1ver, silence is gold.";
	char *copy = strdup(s);
	char *p;

	for (p = strtok(copy, " "); p != NULL; p = strtok(NULL, " "))
		printf("%s\n", p);

	/* this show strtok will kill a string */
	printf("\n\n%s\n", copy);
	free(copy);

	/* So you have to backup your string */
	printf("%s\n", s);

	return 0;
}
