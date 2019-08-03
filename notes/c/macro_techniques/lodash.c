#include <stdio.h>

int main(void)
{
	printf("%s: %d\n", __FILE__, __LINE__);
	printf("function: %s \n", __func__);
	printf("date: %s\n", __DATE__);

	return 0;
}
