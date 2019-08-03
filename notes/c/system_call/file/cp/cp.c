#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1024

static int copy(int read_fd, int write_fd)
{
	int ret;
	int bytes;
	char buf[BUFFER_SIZE];

	for (;;) {
		ret = read(read_fd, buf, BUFFER_SIZE);
		if (ret == -1) {
			perror("read");
			return -1;
		} else if (ret == 0) {
			break;
		}

		bytes = ret;

		ret = write(write_fd, buf, bytes);
		if (ret == -1) {
			perror("write");
			return -1;
		}
	}

	return 0;
}

static int copy_file(const char *from, const char *to)
{
	int ret;
	int read_fd, write_fd;

	/* Check is destonation file exists, If exists, return -1; */
	if (access(from, F_OK) == -1) {
		fprintf(stderr, "source file not exists!\n");
		return -1;
	}
	if (access(to, F_OK) != -1) {
		fprintf(stderr, "destination file already exists!\n");
		return -1;
	}

	/* Open file descriptor */
	read_fd = open(from, O_RDONLY);
	if (read_fd == -1) {
		perror("open");
		return -1;
	}
	write_fd = creat(to, 0644);
	if (write_fd == -1) {
		perror("creat");
		close(read_fd);
		return -1;
	}

	ret = copy(read_fd, write_fd);
	if (ret != 0) {
		close(read_fd);
		close(write_fd);
		return -1;
	}

	close(read_fd);
	close(write_fd);

	return 0;
}

static int copy_to_directory(const char *from, const char *dir)
{
	int ret;
	int read_fd, write_fd;
	char to[128];

	if (access(from, F_OK) == -1) {
		fprintf(stderr, "source file not exists!\n");
		return -1;
	}
	if (access(dir, F_OK) == 0) {
		fprintf(stderr, "destination directory exists!\n");
		return -1;
	}

	ret = mkdir(dir, 0755);
	if (ret != 0) {
		perror("mkdir");
		return -1;
	}

	snprintf(to, 128, "%s/%s", dir, from);

	read_fd = open(from, O_RDONLY);
	if (read_fd < 0) {
		perror("open");
		return -1;
	}
	write_fd = creat(to, 0644);
	if (write_fd < 0) {
		perror("creat");
		close(read_fd);
		return -1;
	}

	ret = copy(read_fd, write_fd);
	if (ret < 0) {
		close(read_fd);
		close(write_fd);
		return -1;
	}

	close(read_fd);
	close(write_fd);

	return 0;
}

static int link_file(const char *from, const char *to)
{
	int ret;

	if (access(from, F_OK) != 0) {
		fprintf(stderr, "source file not exists!\n");
		return -1;
	}
	if (access(to, F_OK) == 0) {
		fprintf(stderr, "destination file alreadt exists!\n");
		return -1;
	}

	ret = symlink(from, to);
	if (ret != 0) {
		perror("symlink");
		return -1;
	}

	return 0;
}

int main(int argc, const char *argv[])
{
	if (strcmp(argv[1], "-d") == 0) {
		const char *from = argv[2];
		const char *dir  = argv[3];

		copy_to_directory(from, dir);
	} else if (strcmp(argv[1], "-s") == 0) {
		const char *from = argv[2];
		const char *to   = argv[3];

		link_file(from, to);
	} else {
		const char *from = argv[1];
		const char *to   = argv[2];

		copy_file(from, to);
	}

	return 0;
}
