#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFER_SIZE 64
#define READ_END 0
#define WRITE_END 1

#define WRITE_MSG "Hello Asshole"

int main(void)
{
	char read_msg[BUFFER_SIZE];
	int fd[2];
	int status;
	pid_t pid;

	if (pipe(fd) == -1) {
		perror("pipe");
		return 1;
	}

	pid = fork();

	if (pid < 0) {
		perror("fork");
		return 1;
	} else if (pid > 0) {
		close(fd[READ_END]);
		write(fd[WRITE_END], WRITE_MSG, strlen(WRITE_MSG) + 1);
		close(fd[WRITE_END]);
		if (wait(&status) == -1)
			perror("wait");
	} else {
		close(fd[WRITE_END]);
		read(fd[READ_END], read_msg, BUFFER_SIZE);
		printf("read %s\n", read_msg);
		close(fd[READ_END]);
	}

	return 0;
}
