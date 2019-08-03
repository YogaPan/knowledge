#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	printf("I'm child process, my pid is %d\n", getpid());
	printf("I'm child process, my ppid is %d\n", getppid());
	abort();
	return 0;
}
