#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>

static int count;

void handler(int sig)
{
	count += 1;
	printf("tick %d\n", count);
}

int main(void)
{
	struct sigaction act;
	struct itimerval t;

	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	if (sigaction(SIGALRM, &act, NULL) == -1)
		perror("sigaction");

	t.it_value.tv_sec = 5;
	t.it_value.tv_usec = 0;
	t.it_interval.tv_sec = 1;
	t.it_interval.tv_usec = 0;

	if (setitimer(ITIMER_REAL, &t, NULL) == -1)
		perror("setitimer");

	for (;;)
		sleep(2);

	return 0;
}
