#include <stdio.h>

static void basic(void);
static void add(void);

int main(void)
{
	basic();
	add();

	return 0;
}

static void basic(void)
{
	int input;
	int output;

	input = 10;
	__asm__ ("movl %1, %%eax\n\t"
		 "addl $10, %%eax\n\t"
		 "movl %%eax, %0\n\t"
		 : "=r" (output) : "r" (input) : "%eax");
	printf("%d\n", output);
}

static void add(void)
{
	int x;
	int y;
	int output;

	x = 2;
	y = 3;
	__asm__ ("addl %%ebx, %%eax"
		 : "=a" (output) : "a" (x), "b" (y));
	printf("%d\n", output);
}
