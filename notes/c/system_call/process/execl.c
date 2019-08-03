#include <stdio.h>
#include <unistd.h>

int main(void)
{
	if (execl("/bin/ls", "ls", "-l", NULL) == -1)
		perror("execl");
	printf("If you see this, you failed.\n");
	return 0;
}
