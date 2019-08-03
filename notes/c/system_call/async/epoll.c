#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>

#define BUFFER_SIZE 1024
#define FD_SIZE 1024
#define EPOLL_EVENTS 100

static void add_event(int epollfd, int fd, int state)
{
	struct epoll_event ev;

	ev.events = state;
	ev.data.fd = fd;
	epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
}

static void delete_event(int epollfd, int fd, int state)
{
	struct epoll_event ev;

	ev.events = state;
	ev.data.fd = fd;
	epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &ev);
}

static void modify_event(int epollfd, int fd, int state)
{
	struct epoll_event ev;

	ev.events = state;
	ev.data.fd = fd;
	epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &ev);
}

int main(void)
{
	int n;
	int retval;
	int epollfd;
	int nfds;
	char buffer[BUFFER_SIZE];
	struct epoll_event events[EPOLL_EVENTS];

	epollfd = epoll_create(32);
	if (epollfd == -1) {
		perror("epoll_create");
		exit(EXIT_FAILURE);
	}

	retval = fcntl(STDIN_FILENO, F_GETFL);
	if (retval == -1) {
		perror("fcntl");
		exit(EXIT_FAILURE);
	}

	retval = fcntl(STDIN_FILENO, F_SETFL, retval | O_NONBLOCK);
	if (retval == -1) {
		perror("fcntl");
		exit(EXIT_FAILURE);
	}

	add_event(epollfd, STDIN_FILENO, EPOLLIN);

	for (;;) {
		printf("loop\n");
		/* nfds = epoll_wait(epollfd, events, EPOLL_EVENTS, 1000); */
		nfds = epoll_wait(epollfd, events, EPOLL_EVENTS, -1);
		if (nfds == -1) {
			perror("epoll_wait");
			exit(EXIT_FAILURE);
		}

		for (n = 0; n < nfds; n++) {
			if (events[n].data.fd == STDIN_FILENO) {
				retval = read(STDIN_FILENO, buffer, BUFFER_SIZE-1);
				if (retval == -1) {
					perror("read");
					exit(EXIT_FAILURE);
				}

				buffer[retval] = '\0';
				printf("%s", buffer);
			}
		}
	}

	delete_event(epollfd, STDIN_FILENO, EPOLLIN);

	return 0;
}
