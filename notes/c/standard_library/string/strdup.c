#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *return_string(const char *src);
void pass_pointer(char *dest, const char *src);

int main(void)
{
	char *str;
	char copy[63+1];

	str = return_string("fuck");
	printf("%s\n", str);
	free(str);

	pass_pointer(copy, "fuck");
	printf("%s\n", copy);

	return 0;
}

char *return_string(const char *src)
{
	return strdup(src);
}

void pass_pointer(char *dest, const char *src)
{
	strncpy(dest, src, 63);
	dest[63] = '\0';
}
