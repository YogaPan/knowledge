#include <stdio.h>

int main(void)
{
	char buf[256+1];
	FILE *fd = popen("ls", "r");

	while (fgets(buf, 256, fd) != NULL)
		printf("%s", buf);
	pclose(fd);

	return 0;
}
