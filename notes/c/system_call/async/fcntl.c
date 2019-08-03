#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

static int show_status(int fd)
{
	int retval;

	retval = fcntl(fd, F_GETFL);

	if (retval < 0) {
		perror("fcntl");
		close(fd);
		exit(EXIT_FAILURE);
	}

	switch(retval & O_ACCMODE) {
	case O_RDONLY:
		printf("Read only\n");
		break;
	case O_WRONLY:
		printf("write only\n");
		break;
	default:
		break;
	}

	if (retval & O_APPEND)
		printf("append\n");

	if (retval & O_NONBLOCK)
		printf("non blocking\n");

	return retval;
}

int main(void)
{
	int read_fd;
	int retval;

	read_fd = open("fcntl.c", O_RDONLY);

	retval = show_status(read_fd);

	retval = fcntl(read_fd, F_SETFL, retval | O_APPEND | O_NONBLOCK);
	if (retval < 0) {
		perror("fcntl");
		close(read_fd);
		return 0;
	}

	show_status(read_fd);

	close(read_fd);

	return 0;
}
