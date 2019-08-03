#include <stdio.h>

#define add(x, y) ((x) + (y))

#define sub(x, y) \
(int)({ \
	 typeof(x) __ret; \
	 __ret = (x) - (y); \
	 __ret; \
})

#define swap(x, y) \
({ \
	typeof(x) __tmp = (x); \
	(x) = (y); \
	(y) = __tmp; \
})

int main(void)
{
	int answer;
	int x;
	int y;

	x = 3;
	y = 4;
	printf("x=%d y=%d\n", x, y);
	swap(x, y);
	printf("x=%d y=%d\n", x, y);

	answer = sub(x, y);
	printf("x-y=%d\n", answer);

	answer = add(x, y);
	printf("x+y=%d\n", answer);

	return 0;
}
