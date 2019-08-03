#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char **argv)
{
	int swd_fd;
	int ret;

	swd_fd = open(".", O_RDONLY);
	if (swd_fd == -1) {
		perror("open");
		exit(EXIT_FAILURE);
	}
	ret = chdir("myServer");
	if (ret == -1) {
		perror("chdir");
		exit(EXIT_FAILURE);
	}

	ret = fchdir(swd_fd);
	if (ret == -1) {
		perror("fchdir");
		exit(EXIT_FAILURE);
	}

	close(swd_fd);
	return 0;
}
