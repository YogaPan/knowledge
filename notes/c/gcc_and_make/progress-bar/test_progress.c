#include <stdio.h>
#include "progress.h"

int main(void)
{
	int i;
	struct progress *p;
	struct progress_bar b = {
		.completed = '=',
		.uncompleted = ' ',
		.head = '>'
	};

	p = progress_init("Download:", 1430, &b);
	progress_tick(p, 320);
	waste_time();
	progress_tick(p, 1);
	waste_time();
	progress_tick(p, 1);
	waste_time();
	progress_tick(p, 73);
	waste_time();
	progress_tick(p, 90);
	waste_time();
	progress_tick(p, 40);
	waste_time();
	for (i = 0; i < 20; i++) {
		progress_tick(p, 73);
		waste_time();
		progress_tick(p, 40);
		waste_time();
	}
	progress_destroy(p);

	return 0;
}
