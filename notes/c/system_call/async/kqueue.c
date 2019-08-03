#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/event.h>

#define BUFFER_SIZE 128

int main(void)
{
	int kq;
	int nev, i;
	int retval;
	char buffer[BUFFER_SIZE];
	struct kevent change;
	struct kevent event;

	struct timespec ts = {
		.tv_sec  = 3,
		.tv_nsec = 0,
	};

	kq = kqueue();
	if (kq == -1) {
		perror("kqueue");
		return 1;
	}
	EV_SET(&change, STDIN_FILENO, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, 0);
	nev = kevent(kq, &change, 1, NULL, 0, &ts);

	for (;;) {
		printf("loop\n");
		nev = kevent(kq, NULL, 0, &event, 1, &ts);

		if (nev == -1) {
			perror("kevent");
			return 1;
		} else {
			if (event.flags & EV_EOF) {
				fprintf(stderr, "Time out!\n");
				continue;
			}

			for (i = 0; i < nev; i++) {
				retval = read(event.ident, buffer, BUFFER_SIZE-1);
				if (retval == -1) {
					perror("read");
					break;
				}

				buffer[retval] = '\0';

				printf("%s", buffer);
			}
		}
		/* EV_SET(&change, STDIN_FILENO, EVFILT_READ, EV_DELETE | EV_ENABLE, 0, 0, 0); */
		/* kevent(kq, &change, 1, NULL, 0, &ts); */
	}

	close(kq);

	return 0;
}
