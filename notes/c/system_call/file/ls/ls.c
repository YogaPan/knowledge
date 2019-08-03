#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>

static inline void show_inode(struct stat *s)
{
	printf("%-10lld ", s->st_ino);
}

static void show_user(struct stat *s)
{
	struct passwd *user;
	struct group  *group;

	user = getpwuid(s->st_uid);
	printf("%-10s ", user->pw_name);

	group = getgrgid(s->st_gid);
	printf("%-7s ", group->gr_name);
}

static void show_mode(struct stat *s)
{
	if (S_ISDIR(s->st_mode))
		printf("d");
	else
		printf("-");

	if (S_IRUSR & s->st_mode)
		printf("r");
	else
		printf("-");
	if (S_IWUSR & s->st_mode)
		printf("w");
	else
		printf("-");
	if (S_IXUSR & s->st_mode)
		printf("x");
	else
		printf("-");

	if (S_IRGRP & s->st_mode)
		printf("r");
	else
		printf("-");
	if (S_IWGRP & s->st_mode)
		printf("w");
	else
		printf("-");
	if (S_IXGRP & s->st_mode)
		printf("x");
	else
		printf("-");

	if (S_IROTH & s->st_mode)
		printf("r");
	else
		printf("-");
	if (S_IWOTH & s->st_mode)
		printf("w");
	else
		printf("-");
	if (S_IXOTH & s->st_mode)
		printf("x");
	else
		printf("-");
	printf("  ");
}

static void show_time(struct stat *s)
{
	struct tm *time;
	char format_time[128];

	time = localtime(&s->st_ctime);
	strftime(format_time, 128, "%b %d %H:%M", time);

	printf("%-10s", format_time);
}

static void show_size(struct stat *s)
{
	long long size;
	char format_size[128];

	size = s->st_size;

	if (size < 1024) {
		snprintf(format_size, 128, "%lldB", s->st_size);
		printf("%-7s", format_size);
	} else {
		snprintf(format_size, 128, "%lldK", s->st_size / 1024);
		printf("%-7s", format_size);
	}
}

static int show_stat(const char *path)
{
	int ret;
	struct stat s;

	if (access(path, F_OK) < 0) {
		fprintf(stderr, "path not exists\n");
		return -1;
	}

	ret = stat(path, &s);
	if (ret < 0) {
		perror("stat");
		return -1;
	}

	show_inode(&s);
	show_mode(&s);
	show_user(&s);
	show_size(&s);
	show_time(&s);
	printf(" %s\n", path);

	return 0;
}

static int list_file(const char *path)
{
	DIR *dir;
	struct dirent *entry;

	dir = opendir(path);
	if (dir == NULL) {
		perror("opendir");
		return -1;
	}

	entry = readdir(dir);
	while (entry != NULL) {
		show_stat(entry->d_name);
		entry = readdir(dir);
	}

	closedir(dir);

	return 0;
}

int main(int argc, const char *argv[])
{
	list_file(".");

	return 0;
}
