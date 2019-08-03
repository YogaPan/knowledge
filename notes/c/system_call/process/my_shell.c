#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFER_SIZE 128

static int running = 1;
static char buffer[BUFFER_SIZE];

static char **split_into_array(char *str)
{
	char **res;
	char *p;
	int n_spaces;

	res = NULL;
	p = strtok(str, " ");
	n_spaces = 0;

	while (p) {
		res = realloc(res, sizeof(char *) * ++n_spaces);
		if (res == NULL) {
			perror("realloc");
			exit(1);
		}
		res[n_spaces-1] = p;
		p = strtok(NULL, " ");
	}

	res = realloc(res, sizeof(char *) * (n_spaces+1));
	res[n_spaces] = NULL;

	return res;
}

static char **get_input(void)
{
	char **res;

	printf("osh> ");
	fflush(stdout);

	fgets(buffer, BUFFER_SIZE, stdin);
	buffer[strcspn(buffer, "\r\n")] = '\0';

	res = split_into_array(buffer);

	return res;
}

int main(void)
{
	int status;
	pid_t pid;
	char **args;

	while (running) {
		args = get_input();
		if (strcmp(args[0], "exit") == 0)
			break;
		if (strcmp(args[0], "cd") == 0) {
			if (chdir(args[1]) == -1)
				perror("chdir");
			continue;
		}

		pid = fork();

		if (pid < 0) {
			perror("fork");
			return 1;
		} else if (pid > 0) {
			if (wait(&status) == -1) {
				perror("wait");
				return 1;
			}
			free(args);
		} else {
			if (execvp(args[0], args) == -1) {
				perror("execlp");
				return 1;
			}
			return 0;
		}
	}

	return 0;
}
