#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#define BUFFER_SIZE 1024
#define HEADER_SIZE 1024

static void inline header_init(char *header, const char *host, const char *path)
{
	snprintf(header, HEADER_SIZE, "GET %s HTTP/1.1\r\nHost: %s\r\n", path, host);
}

static inline void header_write(char *header, const char *line)
{
	int len = strlen(header);
	snprintf(header+len, HEADER_SIZE-len, "%s\r\n", line);
}

static void inline header_end(char *header)
{
	int len = strlen(header);
	snprintf(header+len, HEADER_SIZE-len, "\r\n");
}

static int get_socket(const char *url, const char *port)
{
	int ret;
	int sockfd;
	struct addrinfo hints, *res, *p;
	char ipstr[INET6_ADDRSTRLEN];
	char *ipver;
	void *addr;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	ret = getaddrinfo(url, port, &hints, &res);
	if (ret != 0) {
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(ret));
		return -1;
	}

	for (p = res; p != NULL; p = p->ai_next) {
		sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (sockfd < 0) {
			perror("sockfd");
			continue;
		}

		ret = connect(sockfd, p->ai_addr, p->ai_addrlen);
		if (ret != 0) {
			perror("connect");
			close(sockfd);
			continue;
		}
		break;
	}

	if (p == NULL) {
		fprintf(stderr, "No server found\n");
		close(sockfd);
		freeaddrinfo(res);
		return -1;
	}

	if (p->ai_family == AF_INET) {
		struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
		addr = &ipv4->sin_addr;
		ipver = "IPv4";
	} else {
		struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
		addr = &ipv6->sin6_addr;
		ipver = "IPv6";
	}

	inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));
	printf("%s: %s\n\n", ipver, ipstr);

	freeaddrinfo(res);

	return sockfd;
}

static int send_message(int sockfd, const char *message)
{
	int ret, len;
	int bytes;
	char buf[BUFFER_SIZE];

	len = strlen(message);
	bytes = 0;

	while (bytes < len) {
		ret = send(sockfd, message+bytes, len-bytes, 0);
		if (ret == -1) {
			perror("send");
			return -1;
		}
		bytes += ret;
	}

	for (;;) {
		ret = recv(sockfd, buf, BUFFER_SIZE-1, 0);
		if (ret == -1) {
			perror("recv");
			return -1;
		}
		if (ret != 0) {
			buf[ret] = '\0';
			printf("%s", buf);
			continue;
		}
		break;
	}

	return 0;
}

int main(int argc, const char *argv[])
{
	const char *host = argv[1];
	const char *path = argv[2];
	char header[HEADER_SIZE];
	int sockfd;

	sockfd = get_socket(host, "80");
	if (sockfd == -1) {
		return 0;
	}

	header_init(header, host, path);
	header_write(header, "Connection: close");
	header_write(header, "Accept: *");
	header_end(header);

	send_message(sockfd, header);

	close(sockfd);

	return 0;
}
