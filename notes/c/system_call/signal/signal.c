#include <stdio.h>
#include <signal.h>
#include <unistd.h>

static int running = 1;

void handler(int sig)
{
	if (sig == SIGINT) {
		printf("Good Bye.\n");
		running = 0;
	} else if (sig == SIGQUIT) {
		printf("I want to sleep...\n");
		sleep(3);
		printf("Yeah! I feel great!!\n");
	}
}

int main(void)
{
	struct sigaction act, act2;

	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	if (sigaction(SIGINT, &act, NULL) == -1)
		perror("sigaction");

	act2.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGINT);
	act.sa_flags = SA_SIGINFO;

	if (sigaction(SIGQUIT, &act2, NULL) == -1)
		perror("sigaction");

	while (running);

	return 0;
}
