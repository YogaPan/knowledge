#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

#define for_each_addrinfo(p, res) \
	for ((p) = (res); (p) != NULL; (p) = (p)->ai_next)

int main(void)
{
	int              ret;
	char	         ipstr[INET6_ADDRSTRLEN];
	const void       *addr;
	const char       *ipver;
	struct addrinfo  hints;
	struct addrinfo  *res, *p;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family   = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	ret = getaddrinfo("www.google.com", NULL, &hints, &res);
	if (ret != 0) {
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(ret));
		return 1;
	}

	for_each_addrinfo(p, res) {
		if (p->ai_family == AF_INET) {
			struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;

			addr = &(ipv4->sin_addr);
			ipver = "IPv4";
		} else {
			struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;

			addr = &(ipv6->sin6_addr);
			ipver = "IPv6";
		}
		inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));
		printf("%s: %s\n", ipver, ipstr);
	}

	freeaddrinfo(res);

	return 0;
}
