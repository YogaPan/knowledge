#include <stdio.h>
#include <string.h>

int main(void)
{
	const char *dirty = "fuck you";
	const char *pretty = "handsome boy";
	char copy[32];

	strcpy(copy, dirty);
	printf("%s\n", copy);

	/* This is error. strncpy not add '\0' at the end of the string. */
	strncpy(copy, pretty, 3);
	printf("%s\n", copy);

	/* This one correct. */
	copy[3] = '\0';
	printf("%s\n", copy);

	return 0;
}
