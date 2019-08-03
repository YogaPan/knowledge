#include <stdio.h>
#include <sys/select.h>
#include <sys/time.h>

int main(void)
{
	int retval;
	fd_set rfds;
	struct timeval tv = {
		.tv_sec = 5,
		.tv_usec = 0,
	};

	/* Watch stdin (fd 0) to see when it has input. */
	FD_ZERO(&rfds);
	FD_SET(0, &rfds);

	/* 1 is the maximum fd + 1 */
	retval = select(1, &rfds, NULL, NULL, &tv);
	/* Don't rely on the value of tv now! */

	if (retval == -1)
		perror("select");
	else if (retval)
		printf("Data is available now.\n");
	/* FD_ISSET(0, &rfds) will be true. */
	else
		printf("No data within five seconds.\n");

	return 0;
}
