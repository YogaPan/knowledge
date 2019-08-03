#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static int *glob_var;

int main(void)
{
	int status;
	pid_t pid;

	glob_var = mmap(NULL, sizeof(*glob_var), PROT_READ | PROT_WRITE,
			MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*glob_var = 1;

	pid = fork();

	if (pid < 0) {
		perror("fork");
		return 0;
	} else if (pid == 0) {
		*glob_var = 5;
	} else {
		wait(&status);
		printf("%d\n", *glob_var);
		munmap(glob_var, sizeof(*glob_var));
	}

	return 0;
}
