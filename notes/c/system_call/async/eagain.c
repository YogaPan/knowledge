#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define BUFFER_SIZE 1024

int main(void)
{
	int retval;
	char buffer[BUFFER_SIZE];

	retval = fcntl(STDIN_FILENO, F_GETFL);
	fcntl(STDIN_FILENO, F_SETFL, retval | O_NONBLOCK);

	for (;;) {
		retval = read(STDIN_FILENO, buffer, BUFFER_SIZE-1);

		if (retval == -1) {
			if (errno == EAGAIN) {
				printf("This is the end\n");
				break;
			} else {
				printf("error!!\n");
				break;
			}
		}

		buffer[retval] = '\0';
		printf("%s", buffer);
	}

	return 0;
}
