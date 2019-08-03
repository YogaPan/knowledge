#include <stdio.h>
#include <stdarg.h>

int sum(int n, ...)
{
	int total = 0;
	int i;
	va_list ap;

	va_start(ap, n);
	for (i = 0; i < n; i++)
		total += va_arg(ap, int);
	va_end(ap);
	return total;
}

void print_line(char *first, ...)
{
	char *str;
	va_list ap;

	str = first;
	va_start(ap, first);
	do {
		printf("%s\n", str);
		str = va_arg(ap, char *);
	} while (str != NULL);
	va_end(ap);
}

int main(void)
{
	int answer;

	answer = sum(3, 42, 11, 99);
	printf("%d\n", answer);
	print_line("fuck", "you", "asshole", NULL);
	return 0;
}
