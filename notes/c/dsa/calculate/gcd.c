#include <stdio.h>

static int gcd(int a, int b)
{
	return b == 0 ? a : gcd(b, a % b);
}

int main(void)
{
	int x, y;
	int answer;

	scanf("%d %d", &x, &y);
	answer = gcd(x, y);
	printf("%d\n", answer);

	return 0;
}
