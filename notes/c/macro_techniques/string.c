#include <stdio.h>

#define PRINT_VAR(var) \
	printf("%s=%d\n", #var, var)

#define UNDERLINE_VAR(var) \
	int _##var

#define PRINT_RED(str, ...) \
({ \
	printf("\x1b[31m"); \
	printf(str, ##__VA_ARGS__); \
	printf("\033[0m"); \
})

int main(void)
{
	UNDERLINE_VAR(a);

	_a = 3;
	PRINT_VAR(_a);
	PRINT_RED("fuck %s\n", "you");

	return 0;
}
