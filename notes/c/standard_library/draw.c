#include "draw.h"
#include <unistd.h>

int main(void)
{
	printColor(RED, "%s\n", "Wait 3 seconds...");
	sleep(3);
	clear();
	draw(45, 15, YEL, "%s\n", "A word in the middle of screen!!");

	return 0;
}
