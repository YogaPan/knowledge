#include <stdio.h>
#include <string.h>

int main(void)
{
	int i;
	const char *str = "fcba73";
	const char *keys = "1234567890";

	i = strcspn(str, keys);
	printf("%d\n", i);

	return 0;
}
