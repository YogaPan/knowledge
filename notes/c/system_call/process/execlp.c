#include <stdio.h>
#include <unistd.h>

int main(void)
{
	if (execlp("ls", "ls", "-l", NULL) == -1)
		perror("execlp");
	printf("If you see me, you failed.\n");
	return 0;
}
