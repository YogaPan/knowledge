#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(void)
{
	char cwd1[256];
	char *cwd2;

	if (getcwd(cwd1, 256) == NULL) {
		perror("getcwd");
		return 1;
	}
	printf("%s\n", cwd1);

	cwd2 = getcwd(NULL, 0);
	printf("%s\n", cwd2);
	free(cwd2);

	return 0;
}
