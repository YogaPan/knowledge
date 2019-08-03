#include <stdio.h>
#include <stdlib.h>

struct my_struct {
	char *a;
	long b;
	char c;
};

int main(void)
{
	struct my_struct *my;

	my = malloc(sizeof(*my));

	printf("%p\n", &my->a);
	printf("%p\n", &my->b);
	printf("%p\n", &my->c);

	printf("%ld\n", sizeof(*my));

	return 0;
}
