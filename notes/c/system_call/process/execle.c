#include <stdio.h>
#include <unistd.h>

int main(void)
{
	char * const envp[] = { "AA=11", "BB=22", NULL };
	if (execle("./environ", "environ", NULL, envp) == -1)
		perror("execle");
	printf("If you see me, you failed.\n");
	return 0;
}
