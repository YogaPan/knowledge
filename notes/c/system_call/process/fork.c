#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
	pid_t child_pid;
	int status;

	printf("I'm parent, my pid is %d\n", getpid());
	child_pid = fork();
	if (child_pid == -1)
		perror("fork");
	else if (child_pid == 0)
		execl("./test", "test", NULL);
	else
		printf("I'm parent, my child is %d\n", child_pid);

	if (wait(&status) == -1) {
		perror("wait");
	}

	if (WIFEXITED(status)) {
		printf("Normal termination with exit status=%d\n", WEXITSTATUS(status));
	}
	if (WIFSIGNALED(status)) {
		printf("Killed by signal=%d\n", WTERMSIG(status));
	}
	if (WIFSTOPPED(status)) {
		printf("Stopped by signal=%d\n", WSTOPSIG(status));
	}
	if (WIFCONTINUED(status)) {
		printf("Continued\n");
	}

	return 0;
}
