#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <netdb.h>

#define SERVER_STRING "Server: yoga http\r\n"

static int startup(const char *port);
static void *accept_request(void *arg);
static void headers(int client, const char *filename);
static void not_found(int client);
static void serve_file(int client, const char *filename);
static void cat(int client, FILE *resource);
static int get_line(int client, char *buf, int size);

static int startup(const char *port)
{
	int server_sock = -1;
	int rv, yes = 1;
	struct addrinfo hints, *servinfo, *p;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	rv = getaddrinfo(NULL, port, &hints, &servinfo);
	if (rv != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		exit(1);
	}

	for (p = servinfo; p != NULL; p = p->ai_next) {
		server_sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (server_sock == -1) {
			perror("socket");
			exit(1);
			continue;
		}
		if (setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, \
			       &yes, sizeof(int)) == -1) {
			perror("setsockopt");
			exit(1);
		}
		if (bind(server_sock, p->ai_addr, p->ai_addrlen) == -1) {
			perror("bind");
			exit(1);
			continue;
		}
		break;
	}
	if (p == NULL) {
		fprintf(stderr, "server: failed to bind\n");
		exit(1);
	}
	freeaddrinfo(servinfo);
	if (listen(server_sock, 5) == -1) {
		perror("listen");
		exit(1);
	}

	return server_sock;
}

static void *accept_request(void *arg)
{
	char buf[1024];
	char method [255];
	char url[255];
	char path[512];
	/* int numchars; */
	char *query_string = NULL;
	int cgi = 0;
	size_t i, j;
	struct stat st;
	int client = (int)(intptr_t)arg;

	/* numchars = get_line(client, buf, sizeof(buf)); */
	get_line(client, buf, sizeof(buf));
	i = 0; j = 0;
	while (!isspace(buf[j]) && (i < sizeof(method) - 1)) {
		method[i] = buf[j];
		i++; j++;
	}
	method[i] = '\0';

	i = 0;
	while ((isspace(buf[j])) && (j < sizeof(buf)))
		j++;
	while ((!isspace(buf[j])) && (i < sizeof(url) - 1) && (j < sizeof(buf))) {
		url[i] = buf[j];
		i++; j++;
	}
	url[i] = '\0';

	if (strcasecmp(method, "GET") == 0) {
		query_string = url;
		while ((*query_string != '?') && (*query_string != '\n'))
			query_string++;
		if (*query_string == '?') {
			cgi = 1;
			*query_string = '\0';
			query_string++;
		}
	}

	puts(url);
	sprintf(path, "htdocs%s", url);
	if (path[strlen(path) - 1] == '/')
		strcat(path, "index.html");
	if (stat(path, &st) == -1) {
		not_found(client);
	} else {
		if ((st.st_mode & S_IFMT) == S_IFDIR)
			strcat(path, "/index.html");
		if (!cgi)
			serve_file(client, path);
	}

	close(client);
	return NULL;
}

static int get_line(int sock, char *buf, int size)
{
	int i = 0;
	char c = '\0';
	int n;

	while ((i < size - 1) && (c != '\n')) {
		n = recv(sock, &c, 1, 0);
		if (n > 0) {
			if (c == '\r') {
				n = recv(sock, &c, 1, MSG_PEEK);
				if ((n > 0) && (c == '\n'))
					recv(sock, &c, 1, 0);
				else
					c = '\n';
			}
			buf[i] = c;
			i++;
		} else {
			c = '\n';
		}
	}
	buf[i] = '\0';

	return(i);
}

static void headers(int client, const char *filename)
{
	char buf[1024];
	const char *extname;
	/* (void)filename; */

	extname = strchr(filename, '.') + 1;
	/* puts(extname); */
	if (!strcmp(extname, "css")) {
		extname = "css";
	}

	strcpy(buf, "HTTP/1.0 200 OK \r\n");
	send(client, buf, strlen(buf), 0);
	strcpy(buf, SERVER_STRING);
	send(client, buf, strlen(buf), 0);
	sprintf(buf, "Content-Type: text/%s\r\n", extname);
	send(client, buf, strlen(buf), 0);
	strcpy(buf, "\r\n");
	send(client, buf, strlen(buf), 0);
}

static void not_found(int sock)
{
	char buf[1024];

	sprintf(buf, "HTTP/1.0 404 NOT FOUND\r\n");
	send(sock, buf, strlen(buf), 0);
	sprintf(buf, SERVER_STRING);
	send(sock, buf, strlen(buf), 0);
	sprintf(buf, "Content-Type: text/html\r\n");
	send(sock, buf, strlen(buf), 0);
	sprintf(buf, "\r\n");
	send(sock, buf, strlen(buf), 0);
}

static void cat(int client, FILE *resource)
{
	char buf[1024];

	fgets(buf, sizeof(buf), resource);
	while (!feof(resource)) {
		send(client, buf, strlen(buf), 0);
		fgets(buf, sizeof(buf), resource);
	}
}

static void serve_file(int client, const char *filename)
{
	FILE *resource = NULL;
	/* int numchars = 1; */
	/* char buf[1024]; */

	resource = fopen(filename, "r");
	if (resource == NULL) {
		not_found(client);
	} else {
		headers(client, filename);
		cat(client, resource);
	}
	fclose(resource);
}

int main(int argc, char **argv)
{
	const char *port;
	int server_sock, client_sock;
	struct sockaddr_storage their_addr;
	socklen_t sin_size = sizeof(their_addr);
	pthread_t new_thread;

	if (argc != 2) {
		fprintf(stderr, "usage; httpd port\n");
		exit(1);
	}
	port = argv[1];
	server_sock = startup(port);

	for (;;) {
		client_sock = accept(server_sock,                    \
				     (struct sockaddr *)&their_addr, \
				     &sin_size);
		if (client_sock == -1) {
			perror("accept");
			exit(1);
		}
		if (pthread_create(&new_thread, NULL, accept_request, (void *)(intptr_t)client_sock) != 0) {
			perror("pthread_create");
			exit(1);
		}
	}
	close(server_sock);
	return 0;
}
