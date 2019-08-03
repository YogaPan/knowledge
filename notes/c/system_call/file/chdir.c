#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char **argv)
{
	char swd[256];
	int ret;

	if (!getcwd(swd, 256)) {
		perror("getcwd");
		exit(EXIT_FAILURE);
	}

	ret = chdir("socket");
	if (ret == -1) {
		perror("chdir");
		exit(EXIT_FAILURE);
	}

	ret = chdir(swd);
	if (ret == -1) {
		perror("chdir");
		exit(EXIT_FAILURE);
	}
	return 0;
}
