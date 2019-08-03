#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 32

struct pipe {
	int in;
	int out;
};

int main(void)
{
	struct pipe fds;
	char buffer[BUFFER_SIZE];
	pid_t pid;

	if (pipe((int *)&fds) < 0) {
		perror("pipe");
		return 0;
	}

	pid = fork();

	if (pid == -1) {
		perror("fork");
	} else if (pid == 0) {
		close(fds.out);
		read(fds.in, buffer, BUFFER_SIZE);
		printf("%s", buffer);
		close(fds.in);
	} else {
		close(fds.in);
		strncpy(buffer, "Hello, you are my child!\n", BUFFER_SIZE);
		write(fds.out, buffer, BUFFER_SIZE);
		close(fds.out);
	}

	wait(NULL);

	return 0;
}
