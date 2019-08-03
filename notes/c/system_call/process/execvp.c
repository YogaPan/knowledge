#include <stdio.h>
#include <unistd.h>

int main(void)
{
	char *argv[] = { "ls", "-l", NULL };
	if (execvp("ls", argv) == -1)
		perror("execvp");
	printf("If you see me, you failed.\n");
	return 0;
}
